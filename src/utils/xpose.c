// Taken from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include <float/float32.h>

// NOTE do not enable loop unrolling
#include "../blocksize.h"

void float_xpose(const float_len_t m, const float_len_t n, const float *const restrict x, float *const restrict tx)
{
  for (float_len_t j=0; j<n; j+=BLOCKSIZE)
  {
    for (float_len_t i=0; i<m; i+=BLOCKSIZE)
    {
      for (float_len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (float_len_t row=i; row<i+BLOCKSIZE && row<m; ++row)
          tx[col + n*row] = x[row + m*col];
      }
    }
  }
}
