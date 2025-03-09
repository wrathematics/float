// Modified from the coop package. Copyright (c) 2015-2017 Drew Schmidt

#include "safeomp.h"

#include <Rdefines.h>
#include <stdbool.h>

#include "Rfloat.h"
#include "unroll.h"


static inline void centerscalevec(const float_len_t j, const float_len_t m, float *restrict x, float *restrict colmean, float *restrict colvar)
{
  const float tmp = 1. / ((float) m-1);
  
  const float_len_t mj = m*j;
  *colmean = 0;
  *colvar = 0;
  
  for (float_len_t i=0; i<m; i++)
  {
    float dt = x[i + mj] - *colmean;
    *colmean += dt/((float) i+1);
    *colvar += dt * (x[i + mj] - *colmean);
  }
  
  *colvar = sqrt(*colvar * tmp);
  
  // Remove mean and variance
  SAFE_FOR_SIMD
  for (float_len_t i=0; i<m; i++)
    x[i + mj] = (x[i + mj] - *colmean) / *colvar;
}



static inline float centervec(const float_len_t j, const float_len_t m, float *x)
{
  const float div = 1. / ((float) m);
  
  const float_len_t mj = m*j;
  float colmean = 0;
  
  // Get column mean
  SAFE_FOR_SIMD
  for (float_len_t i=0; i<m; i++)
    colmean += x[i + mj] * div;
  
  // Remove mean from column
  SAFE_FOR_SIMD
  for (float_len_t i=0; i<m; i++)
    x[i + mj] -= colmean;
  
  return colmean;
}



static inline float scalevec(const float_len_t j, const float_len_t m, float *x)
{
  const float div = 1./((float) m-1);
  
  const float_len_t mj = m*j;
  float colvar = 0;
  
  // Get column variance
  SAFE_FOR_SIMD
  for (float_len_t i=0; i<m; i++)
  {
    float tmp = x[i + mj];
    colvar += tmp*tmp*div;
  }
  
  colvar = sqrt(colvar);
  
  // Remove variance from column
  SAFE_FOR_SIMD
  for (float_len_t i=0; i<m; i++)
    x[i + mj] /= colvar;
  
  return colvar;
}



static inline int scaler(const bool centerx, const bool scalex, const float_len_t m, const float_len_t n, float *restrict x, float *restrict colmeans, float *restrict colvars)
{
  if (m == 0 || n == 0)
    return 0;
  
  // Doing both at once, if needed, is more performant
  if (centerx && scalex)
  {
    float colmean;
    float colvar;
    #pragma omp parallel for shared(x) if (m*n > OMP_MIN_SIZE)
    for (float_len_t j=0; j<n; j++)
    {
      centerscalevec(j, m, x, &colmean, &colvar);
      
      colmeans[j] = colmean;
      colvars[j] = colvar;
    }
    
  }
  else if (centerx)
  {
    #pragma omp parallel for shared(x) if (m*n > OMP_MIN_SIZE)
    for (float_len_t j=0; j<n; j++)
      colmeans[j] = centervec(j, m, x);
  }
  else if (scalex) // RMSE
  {
    #pragma omp parallel for shared(x) if (m*n > OMP_MIN_SIZE)
    for (float_len_t j=0; j<n; j++)
      colvars[j] = scalevec(j, m, x);
  }
  
  return 0;
}



SEXP R_scale_spm(SEXP x, SEXP center_, SEXP scale_)
{
  SEXP ret;
  SEXP ret_s4_class, cm_s4_class, cv_s4_class;
  SEXP ret_s4, cm_s4, cv_s4;
  SEXP cm, cv;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  const bool center = INTEGER(center_)[0];
  const bool scale = INTEGER(scale_)[0];
  int ptct = 0;
  float *colmeans, *colvars;
  
  PROTECT(ret = newmat(m, n));
  ptct++;
  memcpy(DATA(ret), DATA(x), (size_t)m*n*sizeof(float));
  
  if (center)
  {
    PROTECT(cm = newvec(n));
    ptct++;
    colmeans = DATA(cm);
  }
  else
  {
    cm = NULL;
    colmeans = NULL;
  }
  
  if (scale)
  {
    PROTECT(cv = newvec(n));
    ptct++;
    colvars = DATA(cv);
  }
  else
  {
    cv = NULL;
    colvars = NULL;
  }
  
  
  scaler(center, scale, m, n, DATA(ret), colmeans, colvars);
  
  PROTECT(ret_s4_class = MAKE_CLASS("float32"));
  PROTECT(ret_s4 = NEW_OBJECT(ret_s4_class));
  ptct += 2;
  SET_SLOT(ret_s4, install("Data"), ret);
  
  if (center)
  {
    PROTECT(cm_s4_class = MAKE_CLASS("float32"));
    PROTECT(cm_s4 = NEW_OBJECT(cm_s4_class));
    ptct += 2;
    SET_SLOT(cm_s4, install("Data"), cm);
    setAttrib(ret_s4, install("scaled:center"), cm_s4);
  }
  
  if (scale)
  {
    PROTECT(cv_s4_class = MAKE_CLASS("float32"));
    PROTECT(cv_s4 = NEW_OBJECT(cv_s4_class));
    ptct += 2;
    SET_SLOT(cv_s4, install("Data"), cv);
    setAttrib(ret_s4, install("scaled:scale"), cv_s4);
  }
  
  UNPROTECT(ptct);
  return ret_s4;
}
