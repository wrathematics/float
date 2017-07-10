#ifndef SPM_TYPES_
#define SPM_TYPES_


#include <stdint.h>
#include <stdbool.h>
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

static inline void d2s(const int m, const int n, const double *const restrict x, float *const restrict y)
{
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      y[i + m*j] = (float) x[i + m*j];
  }
}

static inline void s2d(const int m, const int n, const float *const restrict x, double *const restrict y)
{
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      y[i + m*j] = (double) x[i + m*j];
  }
}



#endif
