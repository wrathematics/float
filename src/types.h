#ifndef SPM_TYPES_
#define SPM_TYPES_


#include <Rinternals.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "cdefs.h"

#define NROWS(x) ((x)->nrows)
#define NCOLS(x) ((x)->ncols)
#define DATA(x) ((x)->data)
#define ISAVEC(x) ((x)->isavec)

typedef int len_t;

// dense matrix
typedef struct matrix_t
{
  bool isavec;
  len_t nrows;
  len_t ncols;
  float *data;
} matrix_t;

typedef matrix_t *const restrict mat_r;
typedef const matrix_t *const restrict cmat_r;

static inline matrix_t *newmat(const len_t m, const len_t n)
{
  matrix_t *ret;
  
  ret = malloc(sizeof(*ret));
  if (ret == NULL)
    error("OOM");
  
  size_t len = MAX((size_t)m*n, 1);
  DATA(ret) = malloc(len * sizeof(float));
  if (DATA(ret) == NULL)
  {
    free(ret);
    error("OOM");
  }
  
  NROWS(ret) = m;
  NCOLS(ret) = n;
  
  ISAVEC(ret) = false;
  
  return ret;
}

static inline matrix_t *newvec(const len_t n)
{
  matrix_t *ret = newmat(n, 1);
  ISAVEC(ret) = true;
  return ret;
}

static inline void freemat(matrix_t *x)
{
  if (DATA(x) != NULL)
    free(DATA(x));
  
  if (x != NULL)
  {
    free(x);
    x = NULL;
  }
}


#endif
