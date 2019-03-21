#include <float/float32.h>
#include <float/slapack.h>

#include "Rfloat.h"


SEXP R_chol2inv_spm(SEXP x, SEXP size_)
{
  SEXP ret;
  int info;
  const float_len_t n = NCOLS(x);
  const int size = INTEGER(size_)[0];
  if (size > n)
    error("'size' cannot exceed ncol(x) = %d\n", n);
  
  PROTECT(ret = newmat(size, size));
  
  if (size == n)
    memcpy(DATA(ret), DATA(x), (size_t)n*n*sizeof(float));
  else
  {
    for (int j=0; j<size; j++)
    {
      for (int i=0; i<size; i++)
        DATA(ret)[i + size*j] = DATA(x)[i + n*j];
    }
  }
  
  F77_CALL(rpotri)(&(int){UPLO_U}, &size, DATA(ret), &size, &info);
  
  if (info != 0)
    error("spotri() returned info=%d\n", info);
  
  float_symmetrize(UPLO_U, size, DATA(ret));
  
  UNPROTECT(1);
  return ret;
}
