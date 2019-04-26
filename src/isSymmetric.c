// Modified from the band package. Copyright (c) 2016 Drew Schmidt

#include "blocksize.h"
#include "Rfloat.h"
#include "unroll.h"


#define EPS 1000*FLT_EPSILON

static inline bool samenum(const float x, const float y)
{
  return (fabsf(x-y) < EPS);
}

static inline bool isSym(const float_len_t n, const float *const restrict x)
{
  for (float_len_t j=0; j<n; j+=BLOCKSIZE)
  {
    for (float_len_t i=j; i<n; i+=BLOCKSIZE)
    {
      for (float_len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (float_len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
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
  const float_len_t m = NROWS(x);
  const float_len_t n = NCOLS(x);
  
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
