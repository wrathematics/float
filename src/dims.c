#include "spm.h"


SEXP R_nrow_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = NROWS(x);
  UNPROTECT(1);
  return ret;
}

SEXP R_ncol_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = NCOLS(x);
  UNPROTECT(1);
  return ret;
}

SEXP R_dim_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  PROTECT(ret = allocVector(INTSXP, 2));
  INTEGER(ret)[0] = NROWS(x);
  INTEGER(ret)[1] = NCOLS(x);
  UNPROTECT(1);
  return ret;
}
