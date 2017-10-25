// Taken from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#ifndef SPM_XPOSE_H_
#define SPM_XPOSE_H_


#include "blocksize.h"
#include "types.h"


static inline void xpose(const len_t m, const len_t n, const float *const restrict x, float *restrict tx)
{
  for (len_t j=0; j<n; j+=BLOCKSIZE)
  {
    for (len_t i=0; i<m; i+=BLOCKSIZE)
    {
      for (len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (len_t row=i; row<i+BLOCKSIZE && row<m; ++row)
          tx[col + n*row] = x[row + m*col];
      }
    }
  }
}


#endif
