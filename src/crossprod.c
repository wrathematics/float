// Modified from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include "blocksize.h"
#include "lapack/wrap.h"
#include "matmult.h"
#include "spm.h"


// // lower triangle of t(x) %*% x
static inline void crossprod(const int m, const int n, const float alpha, const float * const restrict x, float *restrict c)
{
  F77_CALL(rsyrk)(&(int){UPLO_L}, &(int){TRANS_T}, &n, &m, &alpha, x, &m, &(float){0.0}, c, &n);
}

static inline void tcrossprod(const int m, const int n, const float alpha, const float * const restrict x, float *restrict c)
{
  F77_CALL(rsyrk)(&(int){UPLO_L}, &(int){TRANS_N}, &m, &n, &alpha, x, &m, &(float){0.0}, c, &m);
}

static inline void symmetrize(const len_t n, float *restrict x)
{
  // #pragma omp parallel for default(none) shared(x) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
  for (len_t j=0; j<n; j+=BLOCKSIZE)
  {
    for (len_t i=j+1; i<n; i+=BLOCKSIZE)
    {
      for (len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
          x[col + n*row] = x[row + n*col];
      }
    }
  }
}



SEXP R_crossprod_spm(SEXP x)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  PROTECT(ret = newmat(n, n));
  
  crossprod(m, n, 1.0f, FLOAT(x), FLOAT(ret));
  symmetrize(n, FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}

SEXP R_crossprod_spmspm(SEXP x, SEXP y)
{
  SEXP ret;
  if (NROWS(x) != NROWS(y))
    error("non-conformable arguments");
  
  PROTECT(ret = newmat(NCOLS(x), NCOLS(y)));
  
  matmult(true, false, 1.0f, NROWS(x), NCOLS(x), FLOAT(x), NROWS(y), NCOLS(y), FLOAT(y), FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}



SEXP R_tcrossprod_spm(SEXP x)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  PROTECT(ret = newmat(m, m));
  
  tcrossprod(m, n, 1.0f, FLOAT(x), FLOAT(ret));
  symmetrize(m, FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}

SEXP R_tcrossprod_spmspm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (NCOLS(x) != NCOLS(y))
    error("non-conformable arguments");
  
  PROTECT(ret = newmat(NROWS(x), NROWS(y)));
  
  matmult(false, true, 1.0f, NROWS(x), NCOLS(x), FLOAT(x), NROWS(y), NCOLS(y), FLOAT(y), FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}
