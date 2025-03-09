#include <Rdefines.h>

#include "Rfloat.h"
#include "unroll.h"


#define SWEEPER(x,ret,MARGIN,vec,veclen,FUN) \
  { \
    if (MARGIN == 1) \
    { \
      for (float_len_t j=0; j<n; j++) \
      { \
        for (float_len_t i=0; i<m; i++) \
          ret[i + m*j] = x[i + m*j] FUN vec[i % veclen]; \
      } \
    } \
    else \
    { \
      for (float_len_t j=0; j<n; j++) \
      { \
        for (float_len_t i=0; i<m; i++) \
          ret[i + m*j] = x[i + m*j] FUN vec[j % veclen]; \
      } \
    } \
  }

#define RUNOP(OP) \
  { \
    if (TYPEOF(STATS) == INTSXP) \
    { \
      SWEEPER(xf, retf, MARGIN, ivec, veclen, OP); \
    } \
    else \
    { \
      SWEEPER(xf, retf, MARGIN, fvec, veclen, OP); \
    } \
  }
  
SEXP R_sweep_spm(SEXP x, SEXP MARGIN_, SEXP STATS, SEXP FUN_)
{
  SEXP ret;
  int *ivec = NULL;
  float_len_t veclen;
  float *fvec = NULL;
  SEXP tmp;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  const int MARGIN = INTEGER(MARGIN_)[0];
  const char FUN = CHARPT(FUN_, 0)[0];
  
  PROTECT(ret = newmat(m, n));
  float *xf = FLOAT(x);
  float *retf = FLOAT(ret);
  
  if (TYPEOF(STATS) == INTSXP)
  {
    ivec = INTEGER(STATS);
    veclen = XLENGTH(STATS);
  }
  else
  {
    tmp = GET_SLOT(STATS, install("Data"));
    fvec = FLOAT(tmp);
    veclen = XLENGTH(tmp);
  }
  
  if (FUN == '+')
  {
    RUNOP(+);
  }
  else if (FUN == '-')
  {
    RUNOP(-);
  }
  else if (FUN == '*')
  {
    RUNOP(*);
  }
  else if (FUN == '/')
  {
    RUNOP(/);
  }
  else
    error("impossible");
  
  UNPROTECT(1);
  return ret;
}
