#include "spm.h"


static inline void xpose(const int m, const int n, const float *const restrict x, float *restrict tx)
{
  const int blocksize = 8; // TODO check cache line explicitly
  
  for (int j=0; j<n; j+=blocksize)
  {
    for (int i=0; i<m; i+=blocksize)
    {
      for (int col=j; col<j+blocksize && col<n; ++col)
      {
        for (int row=i; row<i+blocksize && row<m; ++row)
          tx[col + n*row] = x[row + m*col];
      }
    }
  }
}



SEXP R_xpose_spm(SEXP x_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  matrix_t *ret = newmat(n, m);
  
  xpose(m, n, DATA(x), DATA(ret));
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
