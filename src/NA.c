// Elements taken from the coop package (src/R_naomit.c)
// Copyright (c) 2016-2017 Drew Schmidt


#include <stdint.h>
#include <string.h>

#include "endianness.h"
#include "NA.h"
#include "spm.h"

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
  NA_FLOAT = get_na_float();
  return R_NilValue;
}



SEXP R_isna_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
    {
      const float tmp = DATA(x)[i + m*j];
      LOGICAL(ret)[i + m*j] = isnanf(tmp) || ISNAf(tmp);
    }
  }
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// na.omit
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include "safeomp.h"

#define INT(x) INTEGER(x)

#define THROW_MEMERR error("unable to allocate necessary memory")
#define R_CHECKMALLOC(ptr) if (ptr == NULL) THROW_MEMERR


// faster to index each element and operate accordingly, but
// this is too memory expensive for most applications
// note: R does this anyway because, well, R...
static SEXP R_naomit_spm_small(const len_t m, const len_t n, const float *const x)
{
  SEXP ret_ptr;
  const size_t len = m*n;
  len_t m_fin = m;
  int *na_vec_ind = (int*) calloc(len, sizeof(*na_vec_ind));
  R_CHECKMALLOC(na_vec_ind);
  
  
  // get indices of NA's
  for (size_t i=0; i<len; i++)
  {
    if (ISNAf(x[i]) || isnanf(x[i]))
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
    return R_NilValue;
  
  // build reduced matrix
  matrix_t *ret = newmat(m_fin, n);
  newRptr(ret, ret_ptr, matfin);
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
  return ret_ptr;
}



static SEXP R_naomit_spm_big(const len_t m, const len_t n, const float *const x)
{
  SEXP ret_ptr;
  len_t m_fin = m;
  int *rows = (int*) calloc(m, sizeof(*rows));
  R_CHECKMALLOC(rows);
  
  // get indices of NA's
  #pragma omp parallel for default(none) shared(rows)
  for (len_t j=0; j<n; j++)
  {
    const len_t mj = m*j;
    
    for (len_t i=0; i<m; i++)
    {
      if (ISNAf(x[i + m*j]) || isnanf(x[i + mj]))
        rows[i] = 1;
    }
  }
  
  // get number of rows of output
  for (len_t i=0; i<m; i++)
    m_fin -= rows[i];
  
  if (m_fin == m)
    return R_NilValue;
  
  matrix_t *ret = newmat(m_fin, n);
  newRptr(ret, ret_ptr, matfin);
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
  return ret_ptr;
}



static SEXP R_naomit_spm_vec(size_t n, const float *const x)
{
  SEXP ret_ptr;
  size_t numna = 0;
  
  for (size_t i=0; i<n; i++)
  {
    if (ISNAf(x[i]) || isnanf(x[i]))
      numna++;
  }
  
  matrix_t *ret = newvec(n-numna);
  newRptr(ret, ret_ptr, matfin);
  
  size_t retpos = 0;
  for (size_t i=0; i<n; i++)
  {
    if (!ISNAf(x[i]) && !isnanf(x[i]))
      DATA(ret)[retpos++] = x[i];
  }
  
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_naomit_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  if (ISAVEC(x))
    return R_naomit_spm_vec(m, DATA(x));
  else if (m*n < OMP_MIN_SIZE)
    ret = R_naomit_spm_small(m, n, DATA(x));
  else
    ret = R_naomit_spm_big(m, n, DATA(x));
  
  if (ret == R_NilValue)
    return x_ptr;
  else
    return ret;
}
