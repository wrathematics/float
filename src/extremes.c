#include <math.h>

#include "NA.h"
#include "spm.h"


// ----------------------------------------------------------------------------
// min/max
// ----------------------------------------------------------------------------

SEXP R_min_spm(SEXP x_ptr, SEXP na_rm)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  float min = (float) INFINITY;
  
  matrix_t *ret = newvec(1);
  newRptr(ret, ret_ptr, matfin);
  
  if (LOGICAL(na_rm)[0])
  {
    for (int j=0; j<n; j++)
    {
      for (int i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!ISNAf(tmp) && !isnanf(tmp) && min > tmp)
          min = tmp;
      }
    }
  }
  else
  {
    for (int j=0; j<n; j++)
    {
      for (int i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (min > tmp)
          min = tmp;
      }
    }
  }
  
  DATA(ret)[0] = min;
  
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_max_spm(SEXP x_ptr, SEXP na_rm)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  float max = (float) -INFINITY;
  
  matrix_t *ret = newvec(1);
  newRptr(ret, ret_ptr, matfin);
  
  if (LOGICAL(na_rm)[0])
  {
    for (int j=0; j<n; j++)
    {
      for (int i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!ISNAf(tmp) && !isnanf(tmp) && max < tmp)
          max = tmp;
      }
    }
  }
  else
  {
    for (int j=0; j<n; j++)
    {
      for (int i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (max < tmp)
          max = tmp;
      }
    }
  }
  
  DATA(ret)[0] = max;
  
  UNPROTECT(1);
  return ret_ptr;
}



// ----------------------------------------------------------------------------
// which-min/max
// ----------------------------------------------------------------------------
