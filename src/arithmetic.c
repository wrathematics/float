#include "spm.h"


// matrix + matrix
static inline matrix_t* add_matmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  const int m = NROWS(x);
  const int n = NCOLS(x);
  if (m != NROWS(y) || n != NCOLS(y))
    error("non-conformable arrays");
  
  matrix_t *ret = newmat(m, n);
  
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      DATA(ret)[i + m*j] = DATA(x)[i + m*j] + DATA(y)[i + m*j];
  }
  
  return ret;
}

// matrix + vector
static inline matrix_t* add_matvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  const int m = NROWS(x);
  const int n = NCOLS(x);
  const size_t ny = NROWS(y);
  const size_t dimprod = (size_t)m*n;
  matrix_t *ret = newmat(m, n);
  
  if (dimprod < ny)
    error("dims [product %zu] do not match the length of object [%d]\n", dimprod, NROWS(y));
  else if (dimprod%ny != 0)
    warning("longer object length is not a multiple of shorter object length\n");
  
  for (size_t i=0; i<dimprod; i++)
    DATA(ret)[i] = DATA(x)[i] + DATA(y)[i%ny];
  
  return ret;
}

// vector + vector
static inline matrix_t* add_vecvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  const size_t nx = (size_t) NROWS(x)*NCOLS(x);
  const size_t ny = (size_t) NROWS(y)*NCOLS(y);
  const size_t nret = MAX(nx, ny);
  matrix_t *ret;
  
  if ((nx > ny && nx%ny != 0) || (nx < ny && ny%nx != 0))
    warning("longer object length is not a multiple of shorter object length\n");
  
  ret = newvec(nret);
  
  for (size_t i=0; i<nret; i++)
    DATA(ret)[i] = DATA(x)[i%nx] + DATA(y)[i%ny];
  
  return ret;
}



SEXP R_add_spm(SEXP x_ptr, SEXP y_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  matrix_t *y = (matrix_t*) getRptr(y_ptr);
  
  matrix_t *ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      ret = add_vecvec(x, y);
    else
      ret = add_matvec(y, x);
  }
  else
  {
    if (ISAVEC(y))
      ret = add_matvec(x, y);
    else
      ret = add_matmat(x, y);
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
