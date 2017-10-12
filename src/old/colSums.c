#include <math.h>

#include "NA.h"
#include "spm.h"


SEXP R_colSums_spm(SEXP x_ptr, SEXP na_rm_)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  matrix_t *ret = newvec(n);
  newRptr(ret, ret_ptr, matfin);
  
  if (na_rm)
  {
    for (len_t j=0; j<n; j++)
    {
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!isnanf(tmp) && !ISNAf(tmp))
          sum += tmp;
      }
      
      DATA(ret)[j] = sum;
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
        sum += DATA(x)[i + m*j];
      
      DATA(ret)[j] = sum;
    }
  }
  
  
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_rowSums_spm(SEXP x_ptr, SEXP na_rm_)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  matrix_t *ret = newvec(m);
  newRptr(ret, ret_ptr, matfin);
  
  memset(DATA(ret), 0, m*sizeof(float));
  
  if (na_rm)
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!isnanf(tmp) && !ISNAf(tmp))
          DATA(ret)[i] += tmp;
      }
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
        DATA(ret)[i] += DATA(x)[i + m*j];
    }
  }
  
  
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_colMeans_spm(SEXP x_ptr, SEXP na_rm_)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  matrix_t *ret = newvec(n);
  newRptr(ret, ret_ptr, matfin);
  
  
  if (na_rm)
  {
    for (len_t j=0; j<n; j++)
    {
      len_t num = m;
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!isnanf(tmp) && !ISNAf(tmp))
          sum += tmp;
        else
          num--;
      }
      
      if (num)
        DATA(ret)[j] = sum / ((float) num);
      else
        DATA(ret)[j] = 0.0f;
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
        sum += DATA(x)[i + m*j];
      
      DATA(ret)[j] = sum / ((float) m);
    }
  }
  
  
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_rowMeans_spm(SEXP x_ptr, SEXP na_rm_)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  matrix_t *ret = newvec(m);
  newRptr(ret, ret_ptr, matfin);
  
  memset(DATA(ret), 0, m*sizeof(float));
  
  if (na_rm)
  {
    len_t *num = malloc(m * sizeof(*num));
    for (len_t i=0; i<m; i++)
      num[i] = n;
    
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
      {
        const float tmp = DATA(x)[i + m*j];
        if (!isnanf(tmp) && !ISNAf(tmp))
          DATA(ret)[i] += tmp;
        else
          num[i]--;
      }
    }
    
    for (len_t i=0; i<m; i++)
    {
      if (num[i])
        DATA(ret)[i] /= ((float) num[i]);
      else
        DATA(ret)[i] = 0.0f;
    }
    
    free(num);
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
        DATA(ret)[i] += DATA(x)[i + m*j];
    }
    
    for (len_t i=0; i<m; i++)
      DATA(ret)[i] /= ((float) n);
  }
  
  
  UNPROTECT(1);
  return ret_ptr;
}
