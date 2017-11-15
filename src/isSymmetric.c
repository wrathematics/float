// Modified from the band package. Copyright (c) 2016 Drew Schmidt

#include "spm.h"


#define EPS 1000*FLT_EPSILON

static inline bool samenum(const float x, const float y)
{
  return (fabsf(x-y) < EPS);
}

static inline bool isSym(const len_t n, const float *const restrict x)
{
  const int blocksize = 8; // TODO check cache line explicitly
  
  for (len_t j=0; j<n; j+=blocksize)
  {
    for (len_t i=j; i<n; i+=blocksize)
    {
      for (len_t col=j; col<j+blocksize && col<n; ++col)
      {
        for (len_t row=i; row<i+blocksize && row<n; ++row)
        {
          const bool check = samenum(x[col + n*row], x[row + n*col]);
          if (!check)
            return false;
        }
      }
    }
  }
  
  return true;
}



SEXP R_isSymmetric_spm(SEXP x)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  PROTECT(ret = allocVector(LGLSXP, 1));
  
  if (m != n)
    LGL(ret) = 0;
  else if (n == 0)
    LGL(ret) = 1;
  else
    LGL(ret) = isSym(n, DATA(x));
  
  UNPROTECT(1);
  return ret;
}
