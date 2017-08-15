#include "spm.h"


#define SWEEPER(x,ret,MARGIN,vec,veclen,FUN) \
  { \
    if (MARGIN == 1) \
    { \
      for (len_t j=0; j<n; j++) \
      { \
        for (len_t i=0; i<m; i++) \
          ret[i + m*j] = x[i + m*j] FUN vec[i % veclen]; \
      } \
    } \
    else \
    { \
      for (len_t j=0; j<n; j++) \
      { \
        for (len_t i=0; i<m; i++) \
          ret[i + m*j] = x[i + m*j] FUN vec[j % veclen]; \
      } \
    } \
  }

SEXP R_sweep_spm(SEXP x_ptr, SEXP MARGIN_, SEXP STATS, SEXP FUN_)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const int MARGIN = INTEGER(MARGIN_)[0];
  const char FUN = CHARPT(FUN_, 0)[0];
  
  matrix_t *ret = newmat(m, n);
  
  if (FUN == '+')
  {
    if (TYPEOF(STATS) == INTSXP)
    {
      int *vec = INTEGER(STATS);
      const int veclen = LENGTH(STATS);
      SWEEPER(DATA(x), DATA(ret), MARGIN, vec, veclen, +);
    }
    else
    {
      matrix_t *vec = getRptr(STATS);
      const int veclen = NROWS(vec)*NCOLS(vec);
      SWEEPER(DATA(x), DATA(ret), MARGIN, DATA(vec), veclen, +);
    }
  }
  else if (FUN == '-')
  {
    if (TYPEOF(STATS) == INTSXP)
    {
      int *vec = INTEGER(STATS);
      const int veclen = LENGTH(STATS);
      SWEEPER(DATA(x), DATA(ret), MARGIN, vec, veclen, -);
    }
    else
    {
      matrix_t *vec = getRptr(STATS);
      const int veclen = NROWS(vec)*NCOLS(vec);
      SWEEPER(DATA(x), DATA(ret), MARGIN, DATA(vec), veclen, -);
    }
  }
  else if (FUN == '*')
  {
    if (TYPEOF(STATS) == INTSXP)
    {
      int *vec = INTEGER(STATS);
      const int veclen = LENGTH(STATS);
      SWEEPER(DATA(x), DATA(ret), MARGIN, vec, veclen, *);
    }
    else
    {
      matrix_t *vec = getRptr(STATS);
      const int veclen = NROWS(vec)*NCOLS(vec);
      SWEEPER(DATA(x), DATA(ret), MARGIN, DATA(vec), veclen, *);
    }
  }
  else if (FUN == '/')
  {
    if (TYPEOF(STATS) == INTSXP)
    {
      int *vec = INTEGER(STATS);
      const int veclen = LENGTH(STATS);
      SWEEPER(DATA(x), DATA(ret), MARGIN, vec, veclen, /);
    }
    else
    {
      matrix_t *vec = getRptr(STATS);
      const int veclen = NROWS(vec)*NCOLS(vec);
      SWEEPER(DATA(x), DATA(ret), MARGIN, DATA(vec), veclen, /);
    }
  }
  else
    error("impossible");
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
