#include "spm.h"


SEXP R_mat2spm(SEXP x)
{
  SEXP ret_ptr;
  matrix_t *ret;
  int m, n;
  
  if (!isMatrix(x))
  {
    m = LENGTH(x);
    n = 1;
    ret = newmat(m, n);
    ISAVEC(ret) = true;
  }
  else
  {
    m = nrows(x);
    n = ncols(x);
    ret = newmat(m, n);
    ISAVEC(ret) = false;
  }
  
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      for (int j=0; j<n; j++)
      {
        for (int i=0; i<m; i++)
          DATA(ret)[i + m*j] = (float) REAL(x)[i + m*j];
      }
      
      break;
    
    
    case INTSXP:
      for (int j=0; j<n; j++)
      {
        for (int i=0; i<m; i++)
          DATA(ret)[i + m*j] = (float) INTEGER(x)[i + m*j];
      }
      
      break;
    
    
    default:
      error("");
  }
  
  newRptr(ret, ret_ptr, matfin);
  // classgets(ret_ptr, mkString("spm"));
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_spm2mat(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  if (n == 1 && ISAVEC(x))
    PROTECT(ret = allocVector(REALSXP, m));
  else
    PROTECT(ret = allocMatrix(REALSXP, m, n));
  
  s2d(m, n, DATA(x), REAL(ret));
  
  UNPROTECT(1);
  return ret;
}
