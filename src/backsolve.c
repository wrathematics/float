#include <float/slapack.h>

#include "Rfloat.h"


// ----------------------------------------------------------------------------
// triangular system
// ----------------------------------------------------------------------------

SEXP R_backsolve_spm(SEXP x, SEXP y, SEXP upper_tri, SEXP xpose, SEXP k_)
{
  int info = 0;
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NROWS(y);
  const float_len_t nrhs = (float_len_t) NCOLS(y);
  const int k = INTEGER(k_)[0];
  const int uplo = INTEGER(upper_tri)[0] ? UPLO_U : UPLO_L;
  const int trans = INTEGER(xpose)[0] ? TRANS_T : TRANS_N;
  const int diag = DIAG_N;
  
  
  if (nrhs == 1)
    PROTECT(ret = newvec(k));
  else
    PROTECT(ret = newmat(k, nrhs));
  
  float *retf = FLOAT(ret);
  float *yf = FLOAT(y);
  
  if (nrhs == 1)
    memcpy(retf, yf, (size_t)k*sizeof(float));
  else
  {
    for (int j=0; j<nrhs; j++)
      memcpy(retf + k*j, yf + n*j, (size_t)k*sizeof(float));
  }
  F77_CALL(rtrtrs)(&uplo, &trans, &diag, &k, &nrhs, DATA(x), &m, retf, &k, &info);
  
  if (info != 0)
    error("strtrs() returned info=%d\n", info);
  
  UNPROTECT(1);
  return ret;
}
