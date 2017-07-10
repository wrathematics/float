#include "spm.h"


#define BLOCKSIZE 16
#define EPS 1000*FLT_EPSILON

static inline bool samenum(const float x, const float y)
{
  return (fabsf(x-y) < EPS);
}

static inline bool isSym(const int n, const float *const restrict x)
{
  for (int j=0; j<n; j+=BLOCKSIZE)
  {
    for (int i=j; i<n; i+=BLOCKSIZE)
    {
      for (int col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (int row=i; row<i+BLOCKSIZE && row<n; ++row)
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



#define LGL(x) LOGICAL(x)[0]

SEXP R_isSymmetric_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  PROTECT(ret = allocVector(LGLSXP, 1));
  
  if (m != n)
  {
    LGL(ret) = 0;
  }
  else if (n == 0)
  {
    LGL(ret) = 1;
  }
  else
  {
    LGL(ret) = isSym(n, DATA(x));
  }
  
  UNPROTECT(1);
  return ret;
}
