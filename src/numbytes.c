#include "spm.h"


SEXP R_numbytes_spm(SEXP x_ptr)
{
  SEXP ret;
  double numbytes;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  numbytes = sizeof(matrix_t) + (m*n*sizeof(float));
  
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = numbytes;
  UNPROTECT(1);
  return ret;
}
