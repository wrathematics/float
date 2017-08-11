#include <math.h>

#include "NA.h"
#include "spm.h"


SEXP R_sum_spm(SEXP x_ptr, SEXP na_rm)
{
  SEXP ret_ptr;
  float sum = 0.0f;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  
  matrix_t *ret = newvec(1);
  newRptr(ret, ret_ptr, matfin);
  
  if (LOGICAL(na_rm)[0])
  {
    for (int j=0; j<n; j++)
    {
      for (int i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!ISNAf(tmp) && !isnanf(tmp))
          sum += tmp;
      }
    }
  }
  else
  {
    for (int j=0; j<n; j++)
    {
      for (int i=0; i<m; i++)
        sum += DATA(x)[i + m*j];
    }
  }
  
  DATA(ret)[0] = sum;
  
  UNPROTECT(1);
  return ret_ptr;
}
