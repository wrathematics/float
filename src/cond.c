#include <math.h>

#include "norm.h"
#include "spm.h"


void strcon_(const char *const restrict norm, const char *const restrict uplo,
  const char *const restrict diag, const int *const restrict n,
  const float *const restrict a, const int *const restrict lda,
  float *const restrict rcond, float *const restrict work,
  int *const restrict iwork, int *const restrict info);

void sgecon_(const char *const restrict norm, const int *const restrict n,
  const float *const restrict a, const int *const restrict lda,
  const float *const restrict anorm, float *const restrict rcond,
  float *const restrict work, int *const restrict iwork,
  int *const restrict info);

void sgetrf_(const int *const restrict m, const int *const restrict n,
  float *const restrict a, const int *const restrict lda,
  int *const restrict ipiv, int *const restrict info);


SEXP R_rcond_spm(SEXP x, SEXP norm_, SEXP triang_)
{
  SEXP ret;
  int info;
  float rcond;
  const len_t n = NROWS(x);
  const int triang = INTEGER(triang_)[0];
  const int ws = triang ? 3 : 4;
  const char norm = CHARPT(norm_, 0)[0];
  
  
  PROTECT(ret = newvec(1));
  
  float *work = malloc(ws*n * sizeof(*work));
  if (work == NULL)
    error("OOM");
  int *iwork = malloc(n * sizeof(*iwork));
  if (iwork == NULL)
  {
    free(work);
    error("OOM");
  }
  
  
  if (triang)
  {
    strcon_(&norm, &(char){'L'}, &(char){'N'}, &n, DATA(x), &n, &rcond, work, iwork, &info);
    free(work);
    free(iwork);
    
    if (info != 0)
      error("strcon() returned info=%d\n", info);
  }
  else
  {
    float xnorm;
    float *tmp;
    int *ipiv;
    
    tmp = malloc(n*n * sizeof(*tmp));
    ipiv = malloc(n * sizeof(*ipiv));
    if (tmp == NULL || ipiv == NULL)
    {
      FREE(tmp); FREE(ipiv); FREE(work); FREE(iwork);
      error("OOM");
    }
    
    memcpy(tmp, DATA(x), n*n*sizeof(*tmp));
    
    if (norm == 'O' || norm == '1')
      xnorm = norm_macs(n, n, tmp);
    else if (norm == 'I')
      xnorm = norm_mars(n, n, tmp);
    
    sgetrf_(&n, &n, tmp, &n, ipiv, &info);
    
    if (info != 0)
    {
      free(tmp);free(ipiv);free(work);free(iwork);
      error("sgetrf() returned info=%d\n", info);
    }
    
    sgecon_(&norm, &n, tmp, &n, &xnorm, &rcond, work, iwork, &info);
    
    free(tmp);
    free(ipiv);
    free(work);
    free(iwork);
    
    if (info != 0)
      error("sgecon() returned info=%d\n", info);
  }
  
  DATA(ret)[0] = rcond;
  
  UNPROTECT(1);
  return ret;
}
