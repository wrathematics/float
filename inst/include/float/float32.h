#ifndef R_FLOAT_FLOAT32_
#define R_FLOAT_FLOAT32_


#include <stdbool.h>

#define FLOAT(x) ((float*) INTEGER(x))

void float_crossprod(const int m, const int n, const float alpha, const float * const restrict x, float *const restrict c);
void float_tcrossprod(const int m, const int n, const float alpha, const float * const restrict x, float *const restrict c);
void float_matmult(const bool transx, const bool transy,
  const float alpha, const int mx, const int nx, const float *const restrict x,
  const int my, const int ny, const float *const restrict y, float *const restrict ret);

void float_symmetrize(const int uplo, const int n, float *const restrict x);

void float_xpose(const int m, const int n, const float *const restrict x, float *const restrict tx);


#endif
