// Modified from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#ifndef SPM_XPOSE_H_
#define SPM_XPOSE_H_


#include "blocksize.h"
#include "lapack/wrap.h"

// uplo: triangle to copy FROM, i.e. uplo=UPLO_L means copy lower to upper
static inline void symmetrize(const int uplo, const len_t n, float *restrict x)
{
  if (uplo == UPLO_L)
  {
    // #pragma omp parallel for default(none) shared(x) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
    for (len_t j=0; j<n; j+=BLOCKSIZE)
    {
      for (len_t i=j+1; i<n; i+=BLOCKSIZE)
      {
        for (len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
            x[col + n*row] = x[row + n*col];
        }
      }
    }
  }
  else
  {
    for (len_t j=0; j<n; j+=BLOCKSIZE)
    {
      for (len_t i=j+1; i<n; i+=BLOCKSIZE)
      {
        for (len_t col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (len_t row=i; row<i+BLOCKSIZE && row<n; ++row)
          x[row + n*col] = x[col + n*row];
        }
      }
    }
  }
}


#endif
