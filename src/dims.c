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

SEXP R_length_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  size_t len = NROWS(x)*NCOLS(x);
  
  if (len > INT_MAX)
  {
    PROTECT(ret = allocVector(INTSXP, 1));
    INTEGER(ret)[0] = (int) len;
  }
  else
  {
    PROTECT(ret = allocVector(REALSXP, 1));
    REAL(ret)[0] = (double) len;
  }
  
  UNPROTECT(1);
  return ret;
}



// for my eyes only
SEXP R_isavec_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = ISAVEC(x);
  UNPROTECT(1);
  return ret;
}
