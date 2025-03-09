// Modified from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include <float/slapack.h>
#include <float/float32.h>

#include "Rfloat.h"


SEXP R_crossprod_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  PROTECT(ret = newmat(n, n));
  
  float_crossprod(m, n, 1.0f, FLOAT(x), FLOAT(ret));
  float_symmetrize(UPLO_L, n, FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}

SEXP R_crossprod_spmspm(SEXP x, SEXP y)
{
  SEXP ret;
  if (NROWS(x) != NROWS(y))
    error("non-conformable arguments");
  
  PROTECT(ret = newmat(NCOLS(x), NCOLS(y)));
  
  float_matmult(true, false, 1.0f, NROWS(x), NCOLS(x), FLOAT(x), NROWS(y), NCOLS(y), FLOAT(y), FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}



SEXP R_tcrossprod_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  PROTECT(ret = newmat(m, m));
  
  float_tcrossprod(m, n, 1.0f, FLOAT(x), FLOAT(ret));
  float_symmetrize(UPLO_L, m, FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}

SEXP R_tcrossprod_spmspm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (NCOLS(x) != NCOLS(y))
    error("non-conformable arguments");
  
  PROTECT(ret = newmat(NROWS(x), NROWS(y)));
  
  float_matmult(false, true, 1.0f, NROWS(x), NCOLS(x), FLOAT(x), NROWS(y), NCOLS(y), FLOAT(y), FLOAT(ret));
  
  UNPROTECT(1);
  return ret;
}
