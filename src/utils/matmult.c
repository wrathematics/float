// Taken from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include <stdbool.h>

#include <float/float32.h>
#include <float/slapack.h>


// lower triangle of t(x) %*% x
void float_crossprod(const float_len_t m, const float_len_t n, const float alpha, const float * const restrict x, float *const restrict c)
{
  F77_CALL(rsyrk)(&(float_len_t){UPLO_L}, &(float_len_t){TRANS_T}, &n, &m, &alpha, x, &m, &(float){0.0}, c, &n);
}

void float_tcrossprod(const float_len_t m, const float_len_t n, const float alpha, const float * const restrict x, float *const restrict c)
{
  F77_CALL(rsyrk)(&(float_len_t){UPLO_L}, &(float_len_t){TRANS_N}, &m, &n, &alpha, x, &m, &(float){0.0}, c, &m);
}



void float_matmult(const bool transx, const bool transy,
  const float alpha, const float_len_t mx, const float_len_t nx, const float *const restrict x,
  const float_len_t my, const float_len_t ny, const float *const restrict y, float *const restrict ret)
{
  // m = # rows of op(x)
  // n = # cols of op(y)
  // k = # cols of op(x)
  float_len_t im, in, ik;
  float_len_t ctransx, ctransy;
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
