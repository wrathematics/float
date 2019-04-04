// Modified from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include <float/float32.h>
#include <float/slapack.h>

#include "../blocksize.h"
#include "../unroll.h"


// uplo: triangle to copy FROM, i.e. uplo=UPLO_L means copy lower to upper
void float_symmetrize(const float_len_t uplo, const float_len_t n, float *const restrict x)
{
  if (uplo == UPLO_L)
  {
    // #pragma omp parallel for default(none) shared(x) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
    for (float_len_t j=0; j<n; j+=BLOCKSIZE)
    {
      for (float_len_t i=j+1; i<n; i+=BLOCKSIZE)
      {
        for (float_len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (float_len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
            x[col + n*row] = x[row + n*col];
        }
      }
    }
  }
  else
  {
    for (float_len_t j=0; j<n; j+=BLOCKSIZE)
    {
      for (float_len_t i=j+1; i<n; i+=BLOCKSIZE)
      {
        for (float_len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (float_len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
          x[row + n*col] = x[col + n*row];
        }
      }
    }
  }
}
