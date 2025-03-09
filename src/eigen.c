// Modified from the band package. Copyright (c) 2016 Drew Schmidt

#include "safeomp.h"

#include <float/slapack.h>

#include "Rfloat.h"
#include "unroll.h"


static inline void reverse_vec(const float_len_t len, float *const x)
{
  float_len_t j = len-1;
  
  for (float_len_t i=0; i<len/2; i++)
  {
    const float tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
    j--;
  }
}



// reverse columns of a column-major matrix
static inline void reverse_mat(const float_len_t m, const float_len_t n, float *const x)
{
  float_len_t last = n - 1;
  
  for (float_len_t j=0; j<n/2; j++)
  {
    #pragma omp parallel for if(m>OMP_MIN_SIZE)
    for (float_len_t i=0; i<m; i++)
    {
      const float tmp = x[i + m*j];
      x[i + m*j] = x[i + m*last];
      x[i + m*last] = tmp;
    }
    
    last--;
  }
}



static inline int eig_sym_rrr(const bool inplace, const bool only_values, const 
int n, float *restrict x, float *restrict values, float *restrict vectors)
{
  int jobz, info;
  float *x_cp;
  float worksize;
  int lwork, liwork;
  int *iwork, *vec_support;
  float *work;
  int nfound;
  
  
  if (!inplace)
  {
    x_cp = malloc(n*n * sizeof(*x_cp));
    if (x_cp == NULL)
    {
      info = BADMALLOC;
      goto cleanup;
    }
    
    memcpy(x_cp, x, n*n*sizeof(float));
  }
  else
    x_cp = x;
  
  if (only_values)
    jobz = JOBZ_N;
  else
    jobz = JOBZ_V;
  
  vec_support = malloc(2*n * sizeof(*vec_support));
  if (vec_support == NULL)
  {
    info = BADMALLOC;
    goto cleanup;
  }
  
  F77_CALL(rsyevr)(&jobz, &(int){RANGE_A}, &(int){UPLO_U}, &n, x_cp, &n, 
    &(float){0.0}, &(float){0.0}, &(int){0}, &(int){0}, &(float){0.0}, 
    &nfound, values, vectors, &n, vec_support, &worksize, &(int){-1}, &liwork,
    &(int){-1}, &info);
  
  lwork = (int) worksize;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    free(vec_support);
    info = BADMALLOC;
    goto cleanup;
  }
  
  iwork = malloc(liwork * sizeof(*iwork));
  if (iwork == NULL)
  {
    free(vec_support);free(work);
    info = BADMALLOC;
    goto cleanup;
  }
  
  F77_CALL(rsyevr)(&jobz, &(int){RANGE_A}, &(int){UPLO_U}, &n, x_cp, &n, 
    &(float){0.0}, &(float){0.0}, &(int){0}, &(int){0}, &(float){0.0}, 
    &nfound, values, vectors, &n, vec_support, work, &lwork, iwork,
    &liwork, &info);
  
  
  free(vec_support);
  free(work);
  free(iwork);
cleanup:
  if (!inplace)
    free(x_cp);
  
  if (info == BADMALLOC) // jobz is safe, so checking against -1 necessarily means OOM
    THROW_MEMERR;
  
  return info;
}



SEXP R_symeig_spm(SEXP x, SEXP onlyvals_, SEXP descending)
{
  SEXP ret, ret_names;
  SEXP values, vectors;
  float *vectors_pass;
  int ptct;
  int info;
  
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  if (m != n)
    error("non-square matrix in 'eigen'\n");
  
  const int onlyvals = INT(onlyvals_);
  
  if (onlyvals)
  {
    vectors = R_NilValue;
    vectors_pass = NULL;
    ptct = 3;
  }
  else
  {
    PROTECT(vectors = newmat(n, n));
    vectors_pass = DATA(vectors);
    ptct = 4;
  }
  
  PROTECT(values = newvec(n));
  
  info = eig_sym_rrr(false, onlyvals, n, DATA(x), DATA(values), vectors_pass);
  
  if (info != 0)
    error("ssyevd() returned info=%d\n", info);
  
  
  if (INT(descending))
  {
    reverse_vec(n, DATA(values));
    if (!onlyvals)
      reverse_mat(n, n, DATA(vectors));
  }
  
  
  PROTECT(ret = allocVector(VECSXP, 2));
  PROTECT(ret_names = allocVector(STRSXP, 2));
  
  SET_VECTOR_ELT(ret, 0, values);
  SET_VECTOR_ELT(ret, 1, vectors);
  SET_STRING_ELT(ret_names, 0, mkChar("values"));
  SET_STRING_ELT(ret_names, 1, mkChar("vectors"));
  setAttrib(ret, R_NamesSymbol, ret_names);
  
  UNPROTECT(ptct);
  return ret;
}
