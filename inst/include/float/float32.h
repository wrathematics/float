#ifndef R_FLOAT_FLOAT32_
#define R_FLOAT_FLOAT32_


#ifdef __cplusplus
  #ifndef restrict
    #define restrict
  #endif
#endif



#ifdef __cplusplus
extern "C" {
#endif

typedef int float_len_t;

#include <stdbool.h>

#define FLOAT(x) ((float*) INTEGER(x))

// NA.c
extern float NA_FLOAT;
extern float R_NaNf;
int ISNAf(const float x);
int ISNANf(const float x);

// utils/matmult.c
void float_crossprod(const float_len_t m, const float_len_t n, const float alpha, const float * const restrict x, float *const restrict c);
void float_tcrossprod(const float_len_t m, const float_len_t n, const float alpha, const float * const restrict x, float *const restrict c);
void float_matmult(const bool transx, const bool transy,
  const float alpha, const float_len_t mx, const float_len_t nx, const float *const restrict x,
  const float_len_t my, const float_len_t ny, const float *const restrict y, float *const restrict ret);

// utils/symmetrize.c
void float_symmetrize(const float_len_t uplo, const float_len_t n, float *const restrict x);

// utils/xpose.c
void float_xpose(const float_len_t m, const float_len_t n, const float *const restrict x, float *const restrict tx);

#ifdef __cplusplus
}
#endif

#endif
