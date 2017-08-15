#include "spm.h"
#include "xpose.h"


SEXP R_xpose_spm(SEXP x_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  matrix_t *ret = newmat(n, m);
  
  xpose(m, n, DATA(x), DATA(ret));
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
