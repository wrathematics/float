#include <Rmath.h>
 
#include "Rfloat.h"
#include "unroll.h"


SEXP R_flrunif_spm(SEXP m_, SEXP n_, SEXP min_, SEXP max_, SEXP isavec)
{
  SEXP ret;
  const float_len_t m = INTEGER(m_)[0];
  const float_len_t n = INTEGER(n_)[0];
  
  const float min = (float) REAL(min_)[0];
  const float max = (float) REAL(max_)[0];
  
  if (LGL(isavec))
    PROTECT(ret = newvec(m*n));
  else
    PROTECT(ret = newmat(m, n));
  
  float *retf = FLOAT(ret);
  
  if (min > max)
  {
    for (size_t i=0; i<((size_t)m*n); i++)
      retf[i] = (float) R_NaN;
  }
  else if (min == max)
  {
    for (size_t i=0; i<((size_t)m*n); i++)
      retf[i] = min;
  }
  else
  {
    GetRNGstate();
    
    for (size_t i=0; i<((size_t)m*n); i++)
      retf[i] = min + (max-min)*((float) unif_rand());
    
    PutRNGstate();
  }
  
  UNPROTECT(1);
  return ret;
}



SEXP R_flrnorm_spm(SEXP m_, SEXP n_, SEXP mean_, SEXP sd_, SEXP isavec)
{
  SEXP ret;
  const float_len_t m = INTEGER(m_)[0];
  const float_len_t n = INTEGER(n_)[0];
  
  const float mean = (float) REAL(mean_)[0];
  const float sd = (float) REAL(sd_)[0];
  
  if (LGL(isavec))
    PROTECT(ret = newvec(m*n));
  else
    PROTECT(ret = newmat(m, n));
  
  float *retf = FLOAT(ret);
  
  GetRNGstate();
  
  for (size_t i=0; i<((size_t)m*n); i++)
    retf[i] = sd * ((float) norm_rand()) + mean;
  
  PutRNGstate();
  
  UNPROTECT(1);
  return ret;
}



SEXP R_flrand_spm(SEXP data_, SEXP start, SEXP len_, SEXP gen_)
{
  const int len = INT(len_);
  float *data = FLOAT(data_) + INT(start) - 1;
  
  if (TYPEOF(gen_) == REALSXP)
  {
    double *gen = REAL(gen_);
    for (int i=0; i<len; i++)
      data[i] = (float) gen[i];
  }
  else if (TYPEOF(gen_) == INTSXP)
  {
    int *gen = INTEGER(gen_);
    for (int i=0; i<len; i++)
      data[i] = (float) gen[i];
  }
  
  return R_NilValue;
}
