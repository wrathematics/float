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

typedef int len_t;

#include <stdbool.h>

#define FLOAT(x) ((float*) INTEGER(x))

// NA.c
extern float NA_FLOAT;
extern float R_NaNf;
int ISNAf(const float x);
int ISNANf(const float x);

// utils/matmult.c
void float_crossprod(const len_t m, const len_t n, const float alpha, const float * const restrict x, float *const restrict c);
void float_tcrossprod(const len_t m, const len_t n, const float alpha, const float * const restrict x, float *const restrict c);
void float_matmult(const bool transx, const bool transy,
  const float alpha, const len_t mx, const len_t nx, const float *const restrict x,
  const len_t my, const len_t ny, const float *const restrict y, float *const restrict ret);

// utils/symmetrize.c
void float_symmetrize(const len_t uplo, const len_t n, float *const restrict x);

// utils/xpose.c
void float_xpose(const len_t m, const len_t n, const float *const restrict x, float *const restrict tx);

#ifdef __cplusplus
}
#endif

#endif
