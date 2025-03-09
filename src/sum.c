#include <math.h>

#include "NA.h"
#include "Rfloat.h"
#include "unroll.h"


SEXP R_sum_spm(SEXP x, SEXP na_rm)
{
  SEXP ret;
  float sum = 0.0f;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  float *xf = FLOAT(x);
  
  PROTECT(ret = newvec(1));
  
  if (LOGICAL(na_rm)[0])
  {
    for (float_len_t j=0; j<n; j++)
    {
      for (float_len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (!ISNAf(tmp) && !isnan(tmp))
          sum += tmp;
      }
    }
  }
  else
  {
    for (float_len_t j=0; j<n; j++)
    {
      for (float_len_t i=0; i<m; i++)
        sum += xf[i + m*j];
    }
  }
  
  DATA(ret)[0] = sum;
  
  UNPROTECT(1);
  return ret;
}
