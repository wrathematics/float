#include "spm.h"

void spotrf_(const char *const restrict uplo, const int *const restrict n,
  float *const restrict a, const int *const restrict lda, int *const restrict info);

SEXP R_chol_spm(SEXP x_ptr)
{
  SEXP ret_ptr;
  int info;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t n = NROWS(x);
  if (n != NCOLS(x))
    error("'a' must be a square matrix");
  
  matrix_t *ret = newmat(n, n);
  memcpy(DATA(ret), DATA(x), (size_t)n*n*sizeof(float));
  
  spotrf_(&(char){'U'}, &n, DATA(ret), &n, &info);
  
  if (info != 0)
    error("spotrf() returned info=%d\n", info);
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=j+1; i<n; i++)
      DATA(ret)[i + n*j] = 0.0f;
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
