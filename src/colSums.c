// Modified from the coop package. Copyright (c) 2016-2017 Drew Schmidt

#include <math.h>

#include "NA.h"
#include "Rfloat.h"


SEXP R_colSums_spm(SEXP x, SEXP na_rm_)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  PROTECT(ret = newvec(n));
  float *xf = FLOAT(x);
  float *retf = FLOAT(ret);
  
  if (na_rm)
  {
    for (len_t j=0; j<n; j++)
    {
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (! isnan(tmp) && !ISNAf(tmp))
          sum += tmp;
      }
      
      retf[j] = sum;
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
        sum += xf[i + m*j];
      
      retf[j] = sum;
    }
  }
  
  
  UNPROTECT(1);
  return ret;
}



SEXP R_rowSums_spm(SEXP x, SEXP na_rm_)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  PROTECT(ret = newvec(m));
  float *xf = FLOAT(x);
  float *retf = FLOAT(ret);
  
  memset(retf, 0, m*sizeof(float));
  
  if (na_rm)
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (! isnan(tmp) && !ISNAf(tmp))
          retf[i] += tmp;
      }
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
        retf[i] += xf[i + m*j];
    }
  }
  
  
  UNPROTECT(1);
  return ret;
}



SEXP R_colMeans_spm(SEXP x, SEXP na_rm_)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  PROTECT(ret = newvec(n));
  float *xf = FLOAT(x);
  float *retf = FLOAT(ret);
  
  if (na_rm)
  {
    for (len_t j=0; j<n; j++)
    {
      len_t num = m;
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (! isnan(tmp) && !ISNAf(tmp))
          sum += tmp;
        else
          num--;
      }
      
      if (num)
        retf[j] = sum / ((float) num);
      else
        retf[j] = 0.0f;
    }
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      float sum = 0.0f;
      for (len_t i=0; i<m; i++)
        sum += xf[i + m*j];
      
      retf[j] = sum / ((float) m);
    }
  }
  
  
  UNPROTECT(1);
  return ret;
}



SEXP R_rowMeans_spm(SEXP x, SEXP na_rm_)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const bool na_rm = LOGICAL(na_rm_)[0];
  
  PROTECT(ret = newvec(m));
  float *xf = FLOAT(x);
  float *retf = FLOAT(ret);
  
  memset(retf, 0, m*sizeof(float));
  
  if (na_rm)
  {
    len_t *num = malloc(m * sizeof(*num));
    for (len_t i=0; i<m; i++)
      num[i] = n;
    
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
      {
        const float tmp = xf[i + m*j];
        if (! isnan(tmp) && !ISNAf(tmp))
          retf[i] += tmp;
        else
          num[i]--;
      }
    }
    
    for (len_t i=0; i<m; i++)
    {
      if (num[i])
        retf[i] /= ((float) num[i]);
      else
        retf[i] = 0.0f;
    }
    
    free(num);
  }
  else
  {
    for (len_t j=0; j<n; j++)
    {
      for (len_t i=0; i<m; i++)
        retf[i] += xf[i + m*j];
    }
    
    for (len_t i=0; i<m; i++)
      retf[i] /= ((float) n);
  }
  
  
  UNPROTECT(1);
  return ret;
}
