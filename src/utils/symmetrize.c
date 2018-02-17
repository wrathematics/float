// Modified from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include <float/slapack.h>

#include "../blocksize.h"
#include "../unroll.h"


// uplo: triangle to copy FROM, i.e. uplo=UPLO_L means copy lower to upper
void float_symmetrize(const int uplo, const int n, float *const restrict x)
{
  if (uplo == UPLO_L)
  {
    // #pragma omp parallel for default(none) shared(x) schedule(dynamic, 1) if(n>OMP_MIN_SIZE)
    for (int j=0; j<n; j+=BLOCKSIZE)
    {
      for (int i=j+1; i<n; i+=BLOCKSIZE)
      {
        for (int col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (int row=i; row<i+BLOCKSIZE && row<n; ++row)
            x[col + n*row] = x[row + n*col];
        }
      }
    }
  }
  else
  {
    for (int j=0; j<n; j+=BLOCKSIZE)
    {
      for (int i=j+1; i<n; i+=BLOCKSIZE)
      {
        for (int col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (int row=i; row<i+BLOCKSIZE && row<n; ++row)
          x[row + n*col] = x[col + n*row];
        }
      }
    }
  }
}
