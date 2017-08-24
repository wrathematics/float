#include "spm.h"
#include "safeomp.h"

#define BADMALLOC -1

#define INT(x) INTEGER(x)[0]

void ssyevr_(const char * const restrict, const char *const restrict, 
  const char *const restrict, const int *const restrict, float *const restrict,
  const int *const restrict, const float *const restrict,
  const float *const restrict, const int *const restrict,
  const int *const restrict, const float *const restrict,
  const int *const restrict, float *const restrict, float *const restrict,
  const int *const restrict, int *const restrict, float *const restrict,
  int *const restrict, int *const restrict, int *const restrict,
  int *const restrict);


static inline void reverse_vec(const len_t len, float *const x)
{
  len_t j = len-1;
  
  SAFE_FOR_SIMD
  for (len_t i=0; i<len/2; i++)
  {
    const float tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
    j--;
  }
}



// reverse columns of a column-major matrix
static inline void reverse_mat(const len_t m, const len_t n, float *const x)
{
  len_t last = n - 1;
  
  for (len_t j=0; j<n/2; j++)
  {
    #pragma omp parallel for if(m>1000)
    for (len_t i=0; i<m; i++)
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
  char jobz;
  int info;
  float *x_cp;
  float worksize;
  int lwork, liwork;
  int *iwork;
  int *vec_support;
  float *work;
  int nfound;
  
  
  if (!inplace)
  {
    x_cp = malloc(n*n * sizeof(*x_cp));
    memcpy(x_cp, x, n*n*sizeof(float));
    // TODO check malloc
  }
  else
    x_cp = x;
  
  if (only_values)
    jobz = 'N';
  else
    jobz = 'V';
  
  vec_support = malloc(2*n * sizeof(*vec_support));
  // TODO check malloc
  
  ssyevr_(&jobz, &(char){'A'}, &(char){'U'}, &n, x_cp, &n, 
    &(float){0.0}, &(float){0.0}, &(int){0}, &(int){0}, &(float){0.0}, 
    &nfound, values, vectors, &n, vec_support, &worksize, &(int){-1}, &liwork,
    &(int){-1}, &info);
  
  lwork = (int) worksize;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    info = BADMALLOC;
    goto cleanup;
  }
  
  iwork = malloc(liwork * sizeof(*iwork));
  if (iwork == NULL)
  {
    free(work);
    info = BADMALLOC;
    goto cleanup;
  }
  
  ssyevr_(&jobz, &(char){'A'}, &(char){'U'}, &n, x_cp, &n, 
    &(float){0.0}, &(float){0.0}, &(int){0}, &(int){0}, &(float){0.0}, 
    &nfound, values, vectors, &n, vec_support, work, &lwork, iwork,
    &liwork, &info);
  
  
  free(vec_support);
  free(work);
  free(iwork);
cleanup:
  if (inplace)
    free(x_cp);
  
  return info;
}



SEXP R_symeig_spm(SEXP x_ptr, SEXP onlyvals_, SEXP descending)
{
  SEXP ret, ret_names;
  SEXP values_ptr, vectors_ptr;
  const int onlyvals = INT(onlyvals_);
  matrix_t *values, *vectors;
  float *vectors_pass;
  int ptct;
  int info;
  
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int n = NROWS(x);
  
  if (onlyvals)
  {
    vectors = NULL;
    vectors_ptr = R_NilValue;
    vectors_pass = NULL;
    ptct = 3;
  }
  else
  {
    vectors = newmat(n, n);
    newRptr(vectors, vectors_ptr, matfin);
    vectors_pass = DATA(vectors);
    ptct = 4;
  }
  
  values = newvec(n);
  newRptr(values, values_ptr, matfin);
  
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
  
  SET_VECTOR_ELT(ret, 0, values_ptr);
  SET_VECTOR_ELT(ret, 1, vectors_ptr);
  SET_STRING_ELT(ret_names, 0, mkChar("values"));
  SET_STRING_ELT(ret_names, 1, mkChar("vectors"));
  setAttrib(ret, R_NamesSymbol, ret_names);
  
  UNPROTECT(ptct);
  return ret;
}
