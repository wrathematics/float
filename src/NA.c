// Elements taken from the coop package (src/R_naomit.c)
// Copyright (c) 2016-2017 Drew Schmidt

#include "safeomp.h"

#include <stdint.h>
#include <string.h>

#include "endianness.h"
#include "NA.h"
#include "Rfloat.h"
#include "unroll.h"



// R uses 0x7ff00000000007a2 for NA_REAL, and 0x7f8007a2 is a reasonable float analogue
float NA_FLOAT; // extern'd in NA.h
float R_NaNf;

static inline float set_na_float(void)
{
  float ret;
  
#if SPM_BOBE
  int32_t x = 0xa207807f;
#else
  int32_t x = 0x7f8007a2;
#endif
  
  memcpy((void*) &ret, (void*) &x, sizeof(ret));
  
  return ret;
}

/*
static inline float set_nan_float()
{
  float ret;
  
#if SPM_BOBE
  uint32_t NaN = 0x0100807f;
#else
  uint32_t NaN = 0x7f800001;
#endif
  
  memcpy((void*) &ret, (void*) &NaN, sizeof(ret));
  
  return ret;
}
*/


int ISNAf(const float x)
{
  if (!isnan(x))
    return 0;
  
  mrb y;
  y.x = x;
  
#if SPM_BOBE
  return y.y[1] == 1954;
#else
  return y.y[0] == 1954;
#endif
}

int ISNANf(const float x)
{
  return isnan(x) && !ISNAf(x);
}



// have to call on package load to set the global NA_FLOAT
SEXP R_init_NAf(void)
{
  SEXP ret;
  PROTECT(ret = newvec(1));
  
  NA_FLOAT = set_na_float();
  FLOAT(ret)[0] = NA_FLOAT;
  
  UNPROTECT(1);
  return ret;
}

SEXP R_init_NaNf(void)
{
  SEXP ret;
  PROTECT(ret = newvec(1));
  
  R_NaNf = set_na_float();
  FLOAT(ret)[0] = R_NaNf;
  
  UNPROTECT(1);
  return ret;
}



SEXP R_isna_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  float *xf = FLOAT(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  for (float_len_t j=0; j<n; j++)
  {
    for (float_len_t i=0; i<m; i++)
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
  const R_xlen_t len = (R_xlen_t) NROWS(x)*NCOLS(x);
  
  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = anyNA(len, DATA(x));
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// na.omit
// ----------------------------------------------------------------------------

#include <stdlib.h>

// faster to index each element and operate accordingly, but
// this is too memory expensive for most applications
// note: R does this anyway because, well, R...
static SEXP R_naomit_spm_small(const float_len_t m, const float_len_t n, const float *const x)
{
  SEXP ret;
  const size_t len = m*n;
  float_len_t m_fin = m;
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
  for (float_len_t j=1; j<n; j++)
  {
    const float_len_t mj = m*j;
    
    for (float_len_t i=0; i<m; i++)
    {
      if (na_vec_ind[i + mj])
        na_vec_ind[i] = 1;
    }
  }
  
  // get number of rows of output
  for (float_len_t i=0; i<m; i++)
    m_fin -= na_vec_ind[i];
  
  if (m_fin == m)
  {
    free(na_vec_ind);
    return R_NilValue;
  }
  
  // build reduced matrix
  PROTECT(ret = newmat(m_fin, n));
  float *ptr = DATA(ret);
  
  for (float_len_t j=0; j<n; j++)
  {
    const float_len_t mj = m*j;
    float_len_t row = 0;
    
    for (float_len_t i=0; i<m; i++)
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



static SEXP R_naomit_spm_big(const float_len_t m, const float_len_t n, const float *const x)
{
  SEXP ret;
  float_len_t m_fin = m;
  int *rows = (int*) calloc(m, sizeof(*rows));
  CHECKMALLOC(rows);
  
  // get indices of NA's
  #pragma omp parallel for default(shared) shared(rows)
  for (float_len_t j=0; j<n; j++)
  {
    const float_len_t mj = m*j;
    
    for (float_len_t i=0; i<m; i++)
    {
      if (ISNAf(x[i + m*j]) || isnan(x[i + mj]))
        rows[i] = 1;
    }
  }
  
  // get number of rows of output
  for (float_len_t i=0; i<m; i++)
    m_fin -= rows[i];
  
  if (m_fin == m)
  {
    free(rows);
    return R_NilValue;
  }
  
  PROTECT(ret = newmat(m_fin, n));
  float *ptr = DATA(ret);
  
  // build reduced matrix
  #pragma omp parallel for default(shared) shared(rows, ptr, m_fin)
  for (float_len_t j=0; j<n; j++)
  {
    const float_len_t mj = m*j;
    float_len_t row = 0;
    
    for (float_len_t i=0; i<m; i++)
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
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
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
