#include <float/float32.h>

#include "Rfloat.h"


SEXP R_xpose_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  PROTECT(ret = newmat(n, m));
  
  float_xpose(m, n, DATA(x), DATA(ret));
  
  UNPROTECT(1);
  return ret;
}
