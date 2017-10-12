#include <limits.h>
#include <math.h>
#include <stdbool.h>

#include "NA.h"
#include "spm.h"


// ----------------------------------------------------------------------------
// min/max
// ----------------------------------------------------------------------------

SEXP R_min_spm(SEXP x_ptr, SEXP na_rm)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  float min = (float) INFINITY;
  
  matrix_t *ret = newvec(1);
  newRptr(ret, ret_ptr, matfin);
  
  if (LOGICAL(na_rm)[0])
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!ISNAf(tmp) && !isnanf(tmp) && min > tmp)
          min = tmp;
      }
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
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
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  float max = (float) -INFINITY;
  
  matrix_t *ret = newvec(1);
  newRptr(ret, ret_ptr, matfin);
  
  if (LOGICAL(na_rm)[0])
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!ISNAf(tmp) && !isnanf(tmp) && max < tmp)
          max = tmp;
      }
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
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

SEXP R_whichmin_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  float min = (float) INFINITY;
  size_t which;
  bool empty = true;
  
  for (size_t i=0; i<((size_t)m*n); i++)
  {
    const float tmp = DATA(x)[i];
    if (!ISNAf(tmp) && !isnanf(tmp) && min > tmp)
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



SEXP R_whichmax_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  float max = (float) -INFINITY;
  size_t which;
  bool empty = true;
  
  for (size_t i=0; i<((size_t)m*n); i++)
  {
    const float tmp = DATA(x)[i];
    if (!ISNAf(tmp) && !isnanf(tmp) && max < tmp)
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
