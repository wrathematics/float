#include <math.h>

#include <float/slapack.h>

#include "norm.h"
#include "Rfloat.h"


SEXP R_rcond_spm(SEXP x, SEXP norm_, SEXP triang_)
{
  SEXP ret;
  int info;
  float rcond;
  const float_len_t n = NROWS(x);
  const int triang = INTEGER(triang_)[0];
  const int ws = triang ? 3 : 4;
  const int norm = CHARPT(norm_, 0)[0] == 'I' ? NORM_I : NORM_O;
  
  
  PROTECT(ret = newvec(1));
  
  float *work = malloc(ws*n * sizeof(*work));
  CHECKMALLOC(work);
  int *iwork = malloc(n * sizeof(*iwork));
  if (iwork == NULL)
  {
    free(work);
    THROW_MEMERR;
  }
  
  
  if (triang)
  {
    F77_CALL(rtrcon)(&norm, &(int){UPLO_L}, &(int){DIAG_N}, &n, DATA(x), &n, &rcond, work, iwork, &info);
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
      THROW_MEMERR;
    }
    
    memcpy(tmp, DATA(x), n*n*sizeof(*tmp));
    
    if (norm == NORM_O)
      xnorm = norm_macs(n, n, tmp);
    else if (norm == NORM_I)
      xnorm = norm_mars(n, n, tmp);
    
    F77_CALL(sgetrf)(&n, &n, tmp, &n, ipiv, &info);
    
    if (info != 0)
    {
      free(tmp);free(ipiv);free(work);free(iwork);
      error("sgetrf() returned info=%d\n", info);
    }
    
    F77_CALL(rgecon)(&norm, &n, tmp, &n, &xnorm, &rcond, work, iwork, &info);
    
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
