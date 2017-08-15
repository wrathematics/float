#include "NA.h"
#include "spm.h"


SEXP R_mat2spm(SEXP x)
{
  SEXP ret_ptr;
  matrix_t *ret;
  len_t m, n;
  
  if (!isMatrix(x))
  {
    m = LENGTH(x);
    n = 1;
    ret = newvec(m);
  }
  else
  {
    m = nrows(x);
    n = ncols(x);
    ret = newmat(m, n);
  }
  
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      for (len_t j=0; j<n; j++)
      {
        for (len_t i=0; i<m; i++)
        {
          const double tmp = REAL(x)[i + m*j];
          if (ISNA(tmp))
            DATA(ret)[i + m*j] = NA_FLOAT;
          else
            DATA(ret)[i + m*j] = (float) tmp;
        }
      }
      
      break;
    
    
    case LGLSXP:
    case INTSXP:
      for (len_t j=0; j<n; j++)
      {
        for (len_t i=0; i<m; i++)
        {
          const int tmp = INTEGER(x)[i + m*j];
          if (tmp == NA_INTEGER)
            DATA(ret)[i + m*j] = NA_FLOAT;
          else
            DATA(ret)[i + m*j] = (float) tmp;
        }
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
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  if (n == 1 && ISAVEC(x))
    PROTECT(ret = allocVector(REALSXP, m));
  else
    PROTECT(ret = allocMatrix(REALSXP, m, n));
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
    {
      const float tmp = DATA(x)[i + m*j];
      if (ISNAf(tmp))
        REAL(ret)[i + m*j] = NA_REAL;
      else
        REAL(ret)[i + m*j] = (double) tmp;
    }
  }
  
  UNPROTECT(1);
  return ret;
}
