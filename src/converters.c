#include "NA.h"
#include "Rfloat.h"
#include "unroll.h"


SEXP R_mat2spm(SEXP x)
{
  SEXP ret_;
  float_len_t m, n;
  
  if (!isMatrix(x))
  {
    m = XLENGTH(x);
    n = 1;
    PROTECT(ret_ = newvec(m));
  }
  else
  {
    m = NROWS(x);
    n = NCOLS(x);
    PROTECT(ret_ = newmat(m, n));
  }
  
  float *const ret = FLOAT(ret_);
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      for (float_len_t j=0; j<n; j++)
      {
        for (float_len_t i=0; i<m; i++)
        {
          const double tmp = REAL(x)[i + m*j];
          if (ISNA(tmp))
            ret[i + m*j] = NA_FLOAT;
          else
            ret[i + m*j] = (float) tmp;
        }
      }
      
      break;
    
    
    case LGLSXP:
    case INTSXP:
      for (float_len_t j=0; j<n; j++)
      {
        for (float_len_t i=0; i<m; i++)
        {
          const int tmp = INTEGER(x)[i + m*j];
          if (tmp == NA_INTEGER)
            ret[i + m*j] = NA_FLOAT;
          else
            ret[i + m*j] = (float) tmp;
        }
      }
      
      break;
    
    
    default:
      error("");
  }
  
  UNPROTECT(1);
  return ret_;
}



SEXP R_spm2mat(SEXP x_)
{
  SEXP ret;
  const float_len_t m = NROWS(x_);
  const float_len_t n = NCOLS(x_);
  const float *x = (float*) INTEGER(x_);
  
  if (n == 1 && ISAVEC(x_))
    PROTECT(ret = allocVector(REALSXP, m));
  else
    PROTECT(ret = allocMatrix(REALSXP, m, n));
  
  for (float_len_t j=0; j<n; j++)
  {
    for (float_len_t i=0; i<m; i++)
    {
      const float tmp = x[i + m*j];
      if (ISNAf(tmp))
        REAL(ret)[i + m*j] = NA_REAL;
      else
        REAL(ret)[i + m*j] = (double) tmp;
    }
  }
  
  UNPROTECT(1);
  return ret;
}



SEXP R_spm2int(SEXP x_)
{
  SEXP ret;
  const float_len_t m = NROWS(x_);
  const float_len_t n = NCOLS(x_);
  const float *x = (float*) INTEGER(x_);
  
  if (n == 1 && ISAVEC(x_))
    PROTECT(ret = allocVector(INTSXP, m));
  else
    PROTECT(ret = allocMatrix(INTSXP, m, n));
  
  for (float_len_t j=0; j<n; j++)
  {
    for (float_len_t i=0; i<m; i++)
    {
      const float tmp = x[i + m*j];
      if (ISNAf(tmp))
        INTEGER(ret)[i + m*j] = NA_INTEGER;
      else
        INTEGER(ret)[i + m*j] = (int) tmp;
    }
  }
  
  UNPROTECT(1);
  return ret;
}
