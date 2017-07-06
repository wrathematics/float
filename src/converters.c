#include "spm.h"

SEXP R_mat2spm(SEXP x)
{
  SEXP ret_ptr;
  matrix_t *ret;
  
  const int m = nrows(x);
  const int n = ncols(x);
  
  ret = newmat(m, n);
  
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
  
  if (n == 1)
    PROTECT(ret = allocVector(REALSXP, m));
  else
    PROTECT(ret = allocMatrix(REALSXP, m, n));
  
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      REAL(ret)[i + m*j] = (double) DATA(x)[i + m*j];
  }
  
  UNPROTECT(1);
  return ret;
}
