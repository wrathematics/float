#include "spm.h"


SEXP R_diag_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  const int min = MIN(m, n);
  
  PROTECT(ret = allocVector(REALSXP, min));
  
  for (int i=0; i<min; i++)
    REAL(ret)[i] = DATA(x)[i + m*i];
  
  UNPROTECT(1);
  return ret;
}
