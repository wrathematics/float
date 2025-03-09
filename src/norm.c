#include <math.h>

#include "norm.h"
#include "Rfloat.h"


SEXP R_norm_spm(SEXP x, SEXP type_)
{
  SEXP ret;
  float norm;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  const char type = CHARPT(type_, 0)[0];
  
  PROTECT(ret = newvec(1));
  
  if (m == 0 || n == 0)
    norm = 0.0f;
  else if (type == 'O' || type == '1')
    norm = norm_macs(m, n, DATA(x));
  else if (type == 'I')
    norm = norm_mars(m, n, DATA(x));
  else if (type == 'F')
    norm = norm_euc(m, n, DATA(x));
  else if (type == 'M')
    norm = norm_maxmod(m, n, DATA(x));
  else
    error("argument type[1]='%c' must be one of 'M','1','O','I','F' or 'E'\n", type);
  
  DATA(ret)[0] = norm;
  
  UNPROTECT(1);
  return ret;
}
