#include "spm.h"


SEXP R_nrow_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  
  if (ISAVEC(x))
    return R_NilValue;
  
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = NROWS(x);
  UNPROTECT(1);
  return ret;
}

SEXP R_ncol_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  
  if (ISAVEC(x))
    return R_NilValue;
  
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = NCOLS(x);
  UNPROTECT(1);
  return ret;
}

SEXP R_NROW_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = NROWS(x);
  UNPROTECT(1);
  return ret;
}

SEXP R_NCOL_spm(SEXP x_ptr)
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
  
  if (ISAVEC(x))
    return(R_NilValue);
  
  
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



SEXP R_dimset_spm(SEXP x_ptr, SEXP value)
{
  int nr=0, nc=0, len;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  
  if (value == R_NilValue)
  {
    NROWS(x) = NROWS(x)*NCOLS(x);
    NCOLS(x) = 1;
    ISAVEC(x) = true;
    return x_ptr;
  }
  
  if (LENGTH(value) == 0)
    error("length-0 dimension vector is invalid\n");
  else if (LENGTH(value) > 2)
    error("\n");
  
  if (TYPEOF(value) != REALSXP && TYPEOF(value) != INTSXP)
    error("dimension must be numeric (double or int)\n");
  
  
  
  if (LENGTH(value) == 1)
  {
    if (TYPEOF(value) == REALSXP)
      len = (int) REAL(value)[0];
    else
      len = INTEGER(value)[0];
  }
  else
  {
    if (TYPEOF(value) == REALSXP)
    {
      nr = REAL(value)[0];
      nc = REAL(value)[1];
      len = nr*nc;
    }
    else
    {
      nr = INTEGER(value)[0];
      nc = INTEGER(value)[1];
      len = nr*nc;
    }
  }
  
  
  
  if (len != NROWS(x)*NCOLS(x))
    error("dims [product %d] do not match the length of object [%d]\n", len, NROWS(x)*NCOLS(x));
  
  if (LENGTH(value) == 1)
  {
    ISAVEC(x) = true;
    NROWS(x) = len;
    NCOLS(x) = 1;
  }
  else
  {
    ISAVEC(x) = false;
    NROWS(x) = nr;
    NCOLS(x) = nc;
  }
  
  return x_ptr;
}
