#include <math.h>

#include "spm.h"

// Don't want to write a slange wrapper; don't make the user compile fortran
// if at all possible

void slassq_(const int *const restrict n, const float *const restrict x,
  const int *const restrict incx, float *const restrict scale,
  float *const restrict sumsq);


// norm = maximum absolute column sum
static inline float norm_macs(const int m, const int n, const float *const restrict x)
{
  float norm = 0.0f;
  
  for (int j=0; j<n; j++)
  {
    float tmp = 0.0f;
    for (int i=0; i<m; i++)
      tmp += fabsf(x[i + m*j]);
    
    if (tmp > norm)
      norm = tmp;
  }
  
  return norm;
}

// maximum absolute row sum
static inline float norm_mars(const int m, const int n, const float *const restrict x)
{
  float norm = 0.0f;
  float *tmp = malloc(m*sizeof(*tmp));
  if (tmp == NULL)
    error("OOM");
  
  memset(tmp, 0.0f, m*sizeof(*tmp));
  
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      tmp[i] += fabsf(x[i + m*j]);
  }
  
  for (int i=0; i<m; i++)
  {
    if (tmp[i] > norm)
      norm = tmp[i];
  }
  
  free(tmp);
  return norm;
}

// euclidean norm
static inline float norm_euc(const int m, const int n, const float *const restrict x)
{
  float scale = 0.0f;
  float sumsq = 1.0f;
  for (int j=0; j<n; j++)
    slassq_(&m, x + m*j, &(int){1}, &scale, &sumsq);
  
  return scale * sqrtf(sumsq);
}

// max modulus
static inline float norm_maxmod(const int m, const int n, const float *const restrict x)
{
  float norm = 0.0f;
  
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
    {
      if (x[i + m*j] > norm)
        norm = x[i + m*j];
    }
  }
  
  return norm;
}



SEXP R_norm_spm(SEXP x_ptr, SEXP type_)
{
  SEXP ret_ptr;
  float norm;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  const char type = CHARPT(type_, 0)[0];
  
  matrix_t *ret = newvec(1);
  newRptr(ret, ret_ptr, matfin);
  
  if (m == 0 || n == 0)
    norm = 0.0f;
  else if (type == 'O')
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
  return ret_ptr;
}
