#include "Rfloat.h"


// ----------------------------------------------------------------------------
// matrix inverse
// ----------------------------------------------------------------------------

void sgetrf_(const int *m, const int *n, float *restrict a, const int *lda, 
  int *restrict ipiv, int *info);

void sgetri_(const int *n, float *restrict a, const int *lda, 
  int *restrict ipiv, float *work, int *lwork, int *info);

static inline int invert(const float_len_t n, float *const restrict x)
{
  int info = 0;
  int *ipiv;
  int lwork;
  float tmp;
  float *work;
  
  // Factor x = LU
  ipiv = malloc(n * sizeof(*ipiv));
  CHECKMALLOC(ipiv);
  
  sgetrf_(&n, &n, x, &n, ipiv, &info);
  if (info != 0)
  {
    free(ipiv);
    error("sgetrf() returned info=%d\n", info);
  }
  
  // Invert
  lwork = -1;
  sgetri_(&n, x, &n, ipiv, &tmp, &lwork, &info);
  if (info != 0)
  {
    free(ipiv);
    error("sgetri() returned info=%d\n", info);
  }
  
  lwork = (int) tmp;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    free(ipiv);
    THROW_MEMERR;
  }
  
  sgetri_(&n, x, &n, ipiv, work, &lwork, &info);
  
  free(work);
  free(ipiv);
  
  if (info != 0)
    error("sgetri() returned info=%d\n", info);
  
  return info;
}



SEXP R_solve_spm(SEXP x)
{
  SEXP ret;
  const float_len_t n = NROWS(x);
  if (n != NCOLS(x))
    error("'a' must be a square matrix");
  
  PROTECT(ret = newmat(n, n));
  memcpy(DATA(ret), DATA(x), (size_t)n*n*sizeof(float));
  
  invert(n, DATA(ret));
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// system
// ----------------------------------------------------------------------------

void sgesv_(const int *const restrict n, const int *const restrict nrhs,
  float *const restrict a, const int *const restrict lda,
  int *const restrict ipiv, const float *const restrict b,
  const int *const restrict ldb, int *const restrict info);

static inline int solve_system(const float_len_t n, const float_len_t nrhs, 
  float *const restrict x, const float *const restrict y)
{
  int info = 0;
  int *ipiv;
  
  ipiv = malloc((size_t)n*sizeof(*ipiv));
  CHECKMALLOC(ipiv);
  
  sgesv_(&n, &nrhs, x, &n, ipiv, y, &n, &info);
  
  if (info != 0)
    error("sgesv() returned info=%d\n", info);
  
  free(ipiv);
  return info;
}



SEXP R_solve_spmspm(SEXP x, SEXP y)
{
  
  SEXP ret;
  const float_len_t m = NROWS(x);
  const float_len_t n = NCOLS(x);
  const float_len_t nrhs = NCOLS(y);
  if (m != n)
    error("'a' (%d x %d) must be square\n", m, n);
  
  if (n != NROWS(y))
    error("'b' (%d x %d) must be compatible with 'a' (%d x %d)\n", NROWS(y), nrhs, m, n);
  
  if (nrhs == 1)
    PROTECT(ret = newvec(n));
  else
    PROTECT(ret = newmat(n, nrhs));
  
  float *tmp = malloc((size_t)n*n*sizeof(*tmp));
  CHECKMALLOC(tmp);
  
  memcpy(tmp, DATA(x), (size_t)n*n*sizeof(*tmp));
  memcpy(DATA(ret), DATA(y), (size_t)n*nrhs*sizeof(float));
  solve_system(n, nrhs, tmp, DATA(ret));
  free(tmp);
  
  UNPROTECT(1);
  return ret;
}
