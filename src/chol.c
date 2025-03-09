#include <float/slapack.h>

#include "Rfloat.h"


SEXP R_chol_spm(SEXP x)
{
  SEXP ret;
  int info;
  const float_len_t n = (float_len_t) NROWS(x);
  if (n != NCOLS(x))
    error("'a' must be a square matrix");
  
  PROTECT(ret = newmat(n, n));
  float *retf = FLOAT(ret);
  memcpy(retf, DATA(x), (size_t)n*n*sizeof(float));
  
  F77_CALL(rpotrf)(&(int){UPLO_U}, &n, retf, &n, &info);
  
  if (info != 0)
    error("spotrf() returned info=%d\n", info);
  
  for (float_len_t j=0; j<n; j++)
  {
    for (float_len_t i=j+1; i<n; i++)
      retf[i + n*j] = 0.0f;
  }
  
  UNPROTECT(1);
  return ret;
}
