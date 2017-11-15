// Taken from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include <stdbool.h>

#include <float/slapack.h>


// lower triangle of t(x) %*% x
void float_crossprod(const int m, const int n, const float alpha, const float * const restrict x, float *const restrict c)
{
  F77_CALL(rsyrk)(&(int){UPLO_L}, &(int){TRANS_T}, &n, &m, &alpha, x, &m, &(float){0.0}, c, &n);
}

void float_tcrossprod(const int m, const int n, const float alpha, const float * const restrict x, float *const restrict c)
{
  F77_CALL(rsyrk)(&(int){UPLO_L}, &(int){TRANS_N}, &m, &n, &alpha, x, &m, &(float){0.0}, c, &m);
}



void float_matmult(const bool transx, const bool transy,
  const float alpha, const int mx, const int nx, const float *const restrict x,
  const int my, const int ny, const float *const restrict y, float *const restrict ret)
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
