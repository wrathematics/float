#include <float/float32.h>

#include "Rfloat.h"


SEXP R_xpose_spm(SEXP x)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  PROTECT(ret = newmat(n, m));
  
  float_xpose(m, n, DATA(x), DATA(ret));
  
  UNPROTECT(1);
  return ret;
}
