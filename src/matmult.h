// Taken from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#ifndef SPM_MATMULT_
#define SPM_MATMULT_


#include <stdbool.h>

#include "lapack/wrap.h"

// dgemm wrapper
static inline void matmult(const bool transx, const bool transy,
  const float alpha, const int mx, const int nx, const float *const restrict x,
  const int my, const int ny, const float *const restrict y, float *restrict ret)
{
  // m = # rows of op(x)
  // n = # cols of op(y)
  // k = # cols of op(x)
  int im, in, ik;
  int ctransx, ctransy;
  static const float zero = 0.;
  
  ctransx = transx ? TRANS_T : TRANS_N;
  ctransy = transy ? TRANS_T : TRANS_N;
  
  if (transx)
  {
    im = nx;
    ik = mx;
  }
  else
  {
    im = mx;
    ik = nx;
  }
  
  in = transy ? my : ny;
  
  F77_CALL(rgemm)(&ctransx, &ctransy, &im, &in, &ik, &alpha, x, &mx, y, &my, &zero, ret, &im);
}


#endif
