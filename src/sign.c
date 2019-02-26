#include <float/slapack.h>

#include "Rfloat.h"

#define SGN(x) ((x)>0?1 : ((x)<0?-1:0))


SEXP R_sign_spm(SEXP x)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(INTSXP, m));
  else
    PROTECT(ret = allocMatrix(INTSXP, m, n));
  
  const float *xp = FLOAT(x);
  int *retp = INTEGER(ret);
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
      retp[i + m*j] = SGN(xp[i + m*j]);
  }
  
  UNPROTECT(1);
  return ret;
}
