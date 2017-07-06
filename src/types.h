#ifndef SPM_TYPES_
#define SPM_TYPES_


#include <stdint.h>
#include <stdbool.h>

#define NROWS(x) ((x)->nrows)
#define NCOLS(x) ((x)->ncols)
#define DATA(x) ((x)->data)

typedef int len_t;

// dense matrix
typedef struct matrix_t
{
  len_t nrows;
  len_t ncols;
  float *data;
} matrix_t;

typedef struct vector_t
{
  len_t len;
  float *data;
} vector_t;

typedef matrix_t *const restrict mat_r;
typedef const matrix_t *const restrict cmat_r;

typedef vector_t *const restrict vec_r;
typedef const vector_t *const restrict cvec_r;

static inline matrix_t *newmat(const len_t m, const len_t n)
{
  matrix_t *ret;
  
  ret = malloc(sizeof(*ret));
  if (ret == NULL)
    error("OOM");
  
  DATA(ret) = malloc((size_t)m*n*sizeof(float));
  if (DATA(ret) == NULL)
  {
    free(ret);
    error("OOM");
  }
  
  NROWS(ret) = m;
  NCOLS(ret) = n;
  
  return ret;
}


#endif
