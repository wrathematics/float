#ifndef SPM_XPOSE_H_
#define SPM_XPOSE_H_


#include "types.h"


static inline void xpose(const len_t m, const len_t n, const float *const restrict x, float *restrict tx)
{
  const int blocksize = 8; // TODO check cache line explicitly
  
  for (len_t j=0; j<n; j+=blocksize)
  {
    for (len_t i=0; i<m; i+=blocksize)
    {
      for (len_t col=j; col<j+blocksize && col<n; ++col)
      {
        for (len_t row=i; row<i+blocksize && row<m; ++row)
          tx[col + n*row] = x[row + m*col];
      }
    }
  }
}


#endif
