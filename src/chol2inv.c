#include "lapack/wrap.h"
#include "spm.h"
#include "symmetrize.h"


SEXP R_chol2inv_spm(SEXP x, SEXP size)
{
  SEXP ret;
  int info;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  // if (n != NCOLS(x))
  //   error("'a' must be a square matrix");
  
  PROTECT(ret = newmat(n, n));
  memcpy(DATA(ret), DATA(x), (size_t)n*n*sizeof(float));
  
  F77_CALL(rpotri)(&(int){UPLO_U}, &n, DATA(ret), &n, &info);
  
  if (info != 0)
    error("spotri() returned info=%d\n", info);
  
  symmetrize(UPLO_U, n, DATA(ret));
  
  UNPROTECT(1);
  return ret;
}
