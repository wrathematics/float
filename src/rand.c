#include "spm.h"
#include <Rmath.h> 


SEXP R_flrunif_spm(SEXP m_, SEXP n_, SEXP min_, SEXP max_, SEXP isavec)
{
  SEXP ret_ptr;
  const len_t m = INTEGER(m_)[0];
  const len_t n = INTEGER(n_)[0];
  
  const float min = (float) REAL(min_)[0];
  const float max = (float) REAL(max_)[0];
  
  matrix_t *ret = newmat(m, n);
  ISAVEC(ret) = LOGICAL(isavec)[0];
  
  
  if (min > max)
  {
    for (size_t i=0; i<((size_t)m*n); i++)
      DATA(ret)[i] = (float) R_NaN;
  }
  else if (min == max)
  {
    for (size_t i=0; i<((size_t)m*n); i++)
      DATA(ret)[i] = min;
  }
  else
  {
    GetRNGstate();
    
    for (size_t i=0; i<((size_t)m*n); i++)
      DATA(ret)[i] = min + (max-min)*((float) unif_rand());
    
    PutRNGstate();
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}


SEXP R_flrnorm_spm(SEXP m_, SEXP n_, SEXP mean_, SEXP sd_, SEXP isavec)
{
  SEXP ret_ptr;
  const len_t m = INTEGER(m_)[0];
  const len_t n = INTEGER(n_)[0];
  
  const float mean = (float) REAL(mean_)[0];
  const float sd = (float) REAL(sd_)[0];
  
  matrix_t *ret = newmat(m, n);
  ISAVEC(ret) = LOGICAL(isavec)[0];
  
  
  GetRNGstate();
  
  for (size_t i=0; i<((size_t)m*n); i++)
    DATA(ret)[i] = sd * ((float) norm_rand()) + mean;
  
  PutRNGstate();
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
