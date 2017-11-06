#include "lapack/wrap.h"
#include "spm.h"
#include "symmetrize.h"


SEXP R_chol2inv_spm(SEXP x, SEXP size_)
{
  SEXP ret;
  int info;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const int size = INTEGER(size_)[0];
  // if (n != NCOLS(x))
  //   error("'a' must be a square matrix");
  
  PROTECT(ret = newmat(size, size));
  // memcpy(DATA(ret), DATA(x), (size_t)n*n*sizeof(float));
  
  for (int j=0; j<size; j++)
  {
    for (int i=0; i<size; i++)
      DATA(ret)[i + size*j] = DATA(x)[i + n*j];
  }
  
  F77_CALL(rpotri)(&(int){UPLO_U}, &size, DATA(ret), &size, &info);
  
  if (info != 0)
    error("spotri() returned info=%d\n", info);
  
  symmetrize(UPLO_U, size, DATA(ret));
  
  UNPROTECT(1);
  return ret;
}
