// Elements taken from the coop package (src/R_naomit.c)
// Copyright (c) 2016-2017 Drew Schmidt

#include <stdint.h>
#include <string.h>

#include "endianness.h"
#include "NA.h"
#include "Rfloat.h"
#include "unroll.h"


// R uses 0x7ff00000000007a2 for NA_REAL, and 0x7f8007a2 is the most reasonable
// float analogue
float NA_FLOAT; // extern'd in spm.h

static inline float get_na_float()
{
  float ret;
  
#if SPM_BOBE
  int32_t x = 0xa207807f;
#else
  int32_t x = 0x7f8007a2;
#endif
  
  memcpy((void*) &ret, (void*) &x, sizeof(float));
  
  return ret;
}

// have to call on package load to set the global NA_FLOAT
SEXP R_init_NA()
{
  SEXP ret;
  PROTECT(ret = newvec(1));
  
  NA_FLOAT = get_na_float();
  FLOAT(ret)[0] = NA_FLOAT;
  
  return ret;
}



SEXP R_isna_spm(SEXP x)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  float *xf = FLOAT(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
    {
      const float tmp = xf[i + m*j];
      LOGICAL(ret)[i + m*j] = isnan(tmp) || ISNAf(tmp);
    }
  }
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// anyNA
// ----------------------------------------------------------------------------

SEXP R_anyNA_spm(SEXP x)
{
  SEXP ret;
  const size_t len = (size_t) NROWS(x)*NCOLS(x);
  
  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = anyNA(len, DATA(x));
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// na.omit
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include "safeomp.h"

// faster to index each element and operate accordingly, but
// this is too memory expensive for most applications
// note: R does this anyway because, well, R...
static SEXP R_naomit_spm_small(const len_t m, const len_t n, const float *const x)
{
  SEXP ret;
  const size_t len = m*n;
  len_t m_fin = m;
  int *na_vec_ind = (int*) calloc(len, sizeof(*na_vec_ind));
  CHECKMALLOC(na_vec_ind);
  
  
  // get indices of NA's
  for (size_t i=0; i<len; i++)
  {
    if (ISNAf(x[i]) || isnan(x[i]))
      na_vec_ind[i] = 1;
  }
  
  // adjust col index; turn first column of the NA indices
  // to track which rows should go
  for (len_t j=1; j<n; j++)
  {
    const len_t mj = m*j;
    
    for (len_t i=0; i<m; i++)
    {
      if (na_vec_ind[i + mj])
        na_vec_ind[i] = 1;
    }
  }
  
  // get number of rows of output
  for (len_t i=0; i<m; i++)
    m_fin -= na_vec_ind[i];
  
  if (m_fin == m)
  {
    free(na_vec_ind);
    return R_NilValue;
  }
  
  // build reduced matrix
  PROTECT(ret = newmat(m_fin, n));
  float *ptr = DATA(ret);
  
  for (len_t j=0; j<n; j++)
  {
    const len_t mj = m*j;
    len_t row = 0;
    
    for (len_t i=0; i<m; i++)
    {
      if (!na_vec_ind[i%m])
      {
        ptr[row + m_fin*j] = x[i + mj];
        row++;
      }
    }
  }
  
  free(na_vec_ind);
  UNPROTECT(1);
  return ret;
}



static SEXP R_naomit_spm_big(const len_t m, const len_t n, const float *const x)
{
  SEXP ret;
  len_t m_fin = m;
  int *rows = (int*) calloc(m, sizeof(*rows));
  CHECKMALLOC(rows);
  
  // get indices of NA's
  #pragma omp parallel for default(none) shared(rows)
  for (len_t j=0; j<n; j++)
  {
    const len_t mj = m*j;
    
    for (len_t i=0; i<m; i++)
    {
      if (ISNAf(x[i + m*j]) || isnan(x[i + mj]))
        rows[i] = 1;
    }
  }
  
  // get number of rows of output
  for (len_t i=0; i<m; i++)
    m_fin -= rows[i];
  
  if (m_fin == m)
  {
    free(rows);
    return R_NilValue;
  }
  
  PROTECT(ret = newmat(m_fin, n));
  float *ptr = DATA(ret);
  
  // build reduced matrix
  #pragma omp parallel for default(none) shared(rows, ptr, m_fin)
  for (len_t j=0; j<n; j++)
  {
    const len_t mj = m*j;
    len_t row = 0;
    
    for (len_t i=0; i<m; i++)
    {
      if (!rows[i])
      {
        ptr[row + m_fin*j] = x[i + mj];
        row++;
      }
    }
  }
  
  free(rows);
  UNPROTECT(1);
  return ret;
}



static SEXP R_naomit_spm_vec(size_t n, const float *const x)
{
  SEXP ret;
  size_t numna = 0;
  
  for (size_t i=0; i<n; i++)
  {
    if (ISNAf(x[i]) || isnan(x[i]))
      numna++;
  }
  
  PROTECT(ret = newvec(n-numna));
  float *retf = FLOAT(ret);
  
  size_t retpos = 0;
  for (size_t i=0; i<n; i++)
  {
    if (!ISNAf(x[i]) && !isnan(x[i]))
      retf[retpos++] = x[i];
  }
  
  UNPROTECT(1);
  return ret;
}



SEXP R_naomit_spm(SEXP x)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  if (ISAVEC(x))
    return R_naomit_spm_vec(m, DATA(x));
  else if (m*n < OMP_MIN_SIZE)
    ret = R_naomit_spm_small(m, n, DATA(x));
  else
    ret = R_naomit_spm_big(m, n, DATA(x));
  
  if (ret == R_NilValue)
    return x;
  else
    return ret;
}
