#include <limits.h>
#include <math.h>
#include <stdbool.h>

#include "NA.h"
#include "Rfloat.h"
#include "unroll.h"


// ----------------------------------------------------------------------------
// min/max
// ----------------------------------------------------------------------------

SEXP R_min_spm(SEXP x, SEXP na_rm)
{
  SEXP ret;
  const float_len_t m = NROWS(x);
  const float_len_t n = NCOLS(x);
  float min = (float) INFINITY;
  
  PROTECT(ret = newvec(1));
  float *xf = FLOAT(x);
  
  if (LOGICAL(na_rm)[0])
  {
    for (float_len_t j=0; j<n; j++)
    {
      for (float_len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (!ISNAf(tmp) && ! isnan(tmp) && min > tmp)
          min = tmp;
      }
    }
  }
  else
  {
    for (float_len_t j=0; j<n; j++)
    {
      for (float_len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (min > tmp)
          min = tmp;
      }
    }
  }
  
  DATA(ret)[0] = min;
  
  UNPROTECT(1);
  return ret;
}



SEXP R_max_spm(SEXP x, SEXP na_rm)
{
  SEXP ret;
  const float_len_t m = NROWS(x);
  const float_len_t n = NCOLS(x);
  float max = (float) -INFINITY;
  
  PROTECT(ret = newvec(1));
  float *xf = FLOAT(x);
  
  if (LOGICAL(na_rm)[0])
  {
    for (float_len_t j=0; j<n; j++)
    {
      for (float_len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (!ISNAf(tmp) && ! isnan(tmp) && max < tmp)
          max = tmp;
      }
    }
  }
  else
  {
    for (float_len_t j=0; j<n; j++)
    {
      for (float_len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (max < tmp)
          max = tmp;
      }
    }
  }
  
  DATA(ret)[0] = max;
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// which-min/max
// ----------------------------------------------------------------------------

SEXP R_whichmin_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = NROWS(x);
  const float_len_t n = NCOLS(x);
  float min = (float) INFINITY;
  size_t which;
  bool empty = true;
  
  float *xf = FLOAT(x);
  
  for (size_t i=0; i<((size_t)m*n); i++)
  {
    const float tmp = xf[i];
    if (!ISNAf(tmp) && ! isnan(tmp) && min > tmp)
    {
      min = tmp;
      which = i+1;
      empty = false;
    }
  }
  
  if (empty)
  {
    PROTECT(ret = allocVector(INTSXP, 0));
  }
  else
  {
    if (which < INT_MAX)
    {
      PROTECT(ret = allocVector(INTSXP, 1));
      INTEGER(ret)[0] = which;
    }
    else
    {
      PROTECT(ret = allocVector(REALSXP, 1));
      REAL(ret)[0] = which;
    }
  }
  
  UNPROTECT(1);
  return ret;
}



SEXP R_whichmax_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = NROWS(x);
  const float_len_t n = NCOLS(x);
  float max = (float) -INFINITY;
  size_t which;
  bool empty = true;
  
  float *xf = FLOAT(x);
  
  for (size_t i=0; i<((size_t)m*n); i++)
  {
    const float tmp = xf[i];
    if (!ISNAf(tmp) && ! isnan(tmp) && max < tmp)
    {
      max = tmp;
      which = i+1;
      empty = false;
    }
  }
  
  if (empty)
  {
    PROTECT(ret = allocVector(INTSXP, 0));
  }
  else
  {
    if (which < INT_MAX)
    {
      PROTECT(ret = allocVector(INTSXP, 1));
      INTEGER(ret)[0] = which;
    }
    else
    {
      PROTECT(ret = allocVector(REALSXP, 1));
      REAL(ret)[0] = which;
    }
  }
  
  UNPROTECT(1);
  return ret;
}
