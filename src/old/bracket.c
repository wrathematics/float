#include "spm.h"

#define INT(x,i) INTEGER(x)[i]

static SEXP bracketchecks_lgl(SEXP ind)
{
  SEXP ret;
  const int len = LENGTH(ind);
  
  for (int i=0; i<len; i++)
  {
    if (INTEGER(ind)[i] == NA_INTEGER)
      error("NA values not supported as indices in [ operation\n");
  }
  
  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = 0;
  UNPROTECT(1);
  return ret;
}

static SEXP bracketchecks_int(SEXP ind)
{
  SEXP ret;
  bool hasneg = false;
  bool has0 = false;
  bool haspos = false;
  const int len = LENGTH(ind);
  
  for (int i=0; i<len; i++)
  {
    const int ind_i = INTEGER(ind)[i];
    
    if (ind_i < 0)
      hasneg = true;
    if (ind_i == 0)
      has0 = true;
    if (ind_i > 0)
      haspos = true;
    if (ind_i == NA_INTEGER)
      error("NA values not supported as indices in [ operation\n");
  }
  
  if (hasneg && haspos)
    error("only 0's may be mixed with negative subscripts\n");
  
  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = has0;
  UNPROTECT(1);
  return ret;
}

SEXP R_bracketchecks_spm(SEXP ind)
{
  if (TYPEOF(ind) == INTSXP)
    return bracketchecks_int(ind);
  else if (TYPEOF(ind) == LGLSXP)
    return bracketchecks_lgl(ind);
  else
    error("invalid subscript type\n");
}



// assume positive integer indices for now
SEXP R_bracket_spm(SEXP x_ptr, SEXP I, SEXP J, SEXP drop)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t mx = NROWS(x);
  const int m = LENGTH(I);
  const int n = LENGTH(J);
  matrix_t *ret;
  
  if (!ISAVEC(x) && INTEGER(drop)[0] && (m == 1 || n == 1))
  {
    if (m == 1)
    {
      ret = newvec(n);
      for (int j=0; j<n; j++)
        DATA(ret)[j] = DATA(x)[INT(I, 0)-1 + mx*(INT(J, j)-1)];
    }
    else
    {
      ret = newvec(m);
      for (int i=0; i<n; i++)
        DATA(ret)[i] = DATA(x)[INT(I, i)-1 + mx*(INT(J, 0)-1)];
    }
  }
  else
  {
    ret = newmat(m, n);
    ISAVEC(ret) = ISAVEC(x);
    
    for (int j=0; j<n; j++)
    {
      const int mJ_j = mx*(INT(J, j) - 1);
      for (int i=0; i<m; i++)
        DATA(ret)[i + m*j] = DATA(x)[INT(I, i)-1 + mJ_j];
    }
  }
  
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
