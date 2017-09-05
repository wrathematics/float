#include "spm.h"


// ----------------------------------------------------------------------------
// triangular system
// ----------------------------------------------------------------------------

void strtrs_(const char *const restrict uplo, const char *const restrict trans,
  const char *const restrict diag, const int *const restrict n,
  const int *const restrict nrhs, const float *const restrict a,
  const int *const restrict lda, float *const restrict b,
  const int *const restrict ldb, int *const restrict info);

SEXP R_backsolve_spm(SEXP x_ptr, SEXP y_ptr, SEXP upper_tri, SEXP xpose, SEXP k_)
{
  int info = 0;
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  matrix_t *y = (matrix_t*) getRptr(y_ptr);
  const len_t m = NROWS(x);
  const len_t n = NROWS(y);
  const len_t nrhs = NCOLS(y);
  const int k = INTEGER(k_)[0];
  const char uplo = INTEGER(upper_tri)[0] ? 'U' : 'L';
  const char trans = INTEGER(xpose)[0] ? 'T' : 'N';
  const char diag = 'N';
  
  matrix_t *ret = newmat(k, nrhs);
  ISAVEC(ret) = ISAVEC(y);
  newRptr(ret, ret_ptr, matfin);
  
  if (nrhs == 1)
    memcpy(DATA(ret), DATA(y), (size_t)k*sizeof(float));
  else
  {
    for (int j=0; j<nrhs; j++)
      memcpy(DATA(ret) + k*j, DATA(y) + n*j, (size_t)k*sizeof(float));
  }
  strtrs_(&uplo, &trans, &diag, &k, &nrhs, DATA(x), &m, DATA(ret), &k, &info);
  
  if (info != 0)
  error("strtrs() returned info=%d\n", info);
  
  UNPROTECT(1);
  return ret_ptr;
}
