#include "spm.h"
#include "matmult.h"


SEXP R_matmult_spm(SEXP x_ptr, SEXP y_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  matrix_t *y = (matrix_t*) getRptr(y_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(y);
  
  if (NCOLS(x) != NROWS(y))
    error("non-conformable arguments");
  
  matrix_t *ret = newmat(m, n);
  
  matmult(false, false, 1.0f, NROWS(x), NCOLS(x), DATA(x), NROWS(y), NCOLS(y),
    DATA(y), DATA(ret));
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
