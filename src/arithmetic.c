#include <math.h>

#include "spm.h"


#define ERR_NONC error("non-conformable arrays")
#define ERR_DIMS(dimprod,nr) error("dims [product %zu] do not match the length of object [%d]\n", dimprod, nr)
#define WARN_LEN warning("longer object length is not a multiple of shorter object length\n")

#define BINOP_MATMAT(x,y,FUN) \
  const int m = NROWS(x); \
  const int n = NCOLS(x); \
  if (m != NROWS(y) || n != NCOLS(y)) \
    ERR_NONC; \
  \
  matrix_t *ret = newmat(m, n); \
  \
  for (int j=0; j<n; j++) \
  { \
    for (int i=0; i<m; i++) \
      DATA(ret)[i + m*j] = DATA(x)[i + m*j] FUN DATA(y)[i + m*j]; \
  } \
  \
  return ret;

#define BINOP_MATVEC(x,y,FUN) \
  const int m = NROWS(x); \
  const int n = NCOLS(x); \
  const size_t ny = NROWS(y); \
  const size_t dimprod = (size_t)m*n; \
  matrix_t *ret = newmat(m, n); \
  \
  if (dimprod < ny) \
    ERR_DIMS(dimprod, NROWS(y)); \
  else if (dimprod%ny != 0) \
    WARN_LEN; \
  \
  for (size_t i=0; i<dimprod; i++) \
    DATA(ret)[i] = DATA(x)[i] FUN DATA(y)[i%ny]; \
  \
  return ret;

#define BINOP_VECMAT(x,y,FUN) \
  const int m = NROWS(y); \
  const int n = NCOLS(y); \
  const size_t nx = NROWS(x); \
  const size_t dimprod = (size_t)m*n; \
  matrix_t *ret = newmat(m, n); \
  \
  if (dimprod < nx) \
    ERR_DIMS(dimprod, NROWS(x)); \
  else if (dimprod%nx != 0) \
    WARN_LEN; \
  \
  for (size_t i=0; i<dimprod; i++) \
    DATA(ret)[i] = DATA(x)[i%nx] FUN DATA(y)[i]; \
  \
  return ret;

#define BINOP_VECVEC(x,y,FUN) \
  const size_t nx = (size_t) NROWS(x)*NCOLS(x); \
  const size_t ny = (size_t) NROWS(y)*NCOLS(y); \
  const size_t nret = MAX(nx, ny); \
  matrix_t *ret; \
  \
  if ((nx > ny && nx%ny != 0) || (nx < ny && ny%nx != 0)) \
    WARN_LEN; \
  \
  ret = newvec(nret); \
  \
  for (size_t i=0; i<nret; i++) \
    DATA(ret)[i] = DATA(x)[i%nx] FUN DATA(y)[i%ny]; \
  \
  return ret;



// +
static inline matrix_t* add_matmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATMAT(x, y, +);
}

static inline matrix_t* add_matvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATVEC(x, y, +);
}

static inline matrix_t* add_vecvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_VECVEC(x, y, +);
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




// *
static inline matrix_t* mul_matmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATMAT(x, y, *);
}

static inline matrix_t* mul_matvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATVEC(x, y, *);
}

static inline matrix_t* mul_vecvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_VECVEC(x, y, *);
}



SEXP R_mul_spm(SEXP x_ptr, SEXP y_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  matrix_t *y = (matrix_t*) getRptr(y_ptr);
  
  matrix_t *ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      ret = mul_vecvec(x, y);
    else
      ret = mul_matvec(y, x);
  }
  else
  {
    if (ISAVEC(y))
      ret = mul_matvec(x, y);
    else
      ret = mul_matmat(x, y);
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}



// -
static inline matrix_t* sub_matmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATMAT(x, y, -);
}

static inline matrix_t* sub_matvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATVEC(x, y, -);
}

static inline matrix_t* sub_vecmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_VECMAT(x, y, -);
}

static inline matrix_t* sub_vecvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_VECVEC(x, y, -);
}



SEXP R_sub_spm(SEXP x_ptr, SEXP y_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  matrix_t *y = (matrix_t*) getRptr(y_ptr);
  
  matrix_t *ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      ret = sub_vecvec(x, y);
    else
      ret = sub_vecmat(x, y);
  }
  else
  {
    if (ISAVEC(y))
      ret = sub_matvec(x, y);
    else
      ret = sub_matmat(x, y);
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}




// /
static inline matrix_t* div_matmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATMAT(x, y, /);
}

static inline matrix_t* div_matvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_MATVEC(x, y, /);
}

static inline matrix_t* div_vecmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_VECMAT(x, y, /);
}

static inline matrix_t* div_vecvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  BINOP_VECVEC(x, y, /);
}



SEXP R_div_spm(SEXP x_ptr, SEXP y_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  matrix_t *y = (matrix_t*) getRptr(y_ptr);
  
  matrix_t *ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      ret = div_vecvec(x, y);
    else
      ret = div_vecmat(x, y);
  }
  else
  {
    if (ISAVEC(y))
      ret = div_matvec(x, y);
    else
      ret = div_matmat(x, y);
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}



// ^
static inline matrix_t* pow_matmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  const int m = NROWS(x);
  const int n = NCOLS(x);
  if (m != NROWS(y) || n != NCOLS(y))
    ERR_NONC;
  
  matrix_t *ret = newmat(m, n);
  
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      DATA(ret)[i + m*j] = pow(DATA(x)[i + m*j], DATA(y)[i + m*j]);
  }
  
  return ret;
}

static inline matrix_t* pow_matvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  const int m = NROWS(x);
  const int n = NCOLS(x);
  const size_t ny = NROWS(y);
  const size_t dimprod = (size_t)m*n;
  matrix_t *ret = newmat(m, n);
  
  if (dimprod < ny)
    ERR_DIMS(dimprod, NROWS(y));
  else if (dimprod%ny != 0)
    WARN_LEN;
  
  for (size_t i=0; i<dimprod; i++)
    DATA(ret)[i] = pow(DATA(x)[i], DATA(y)[i%ny]);
  
  return ret;
}

static inline matrix_t* pow_vecmat(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  const int m = NROWS(y);
  const int n = NCOLS(y);
  const size_t nx = NROWS(x);
  const size_t dimprod = (size_t)m*n;
  matrix_t *ret = newmat(m, n);
  
  if (dimprod < nx)
    ERR_DIMS(dimprod, NROWS(x));
  else if (dimprod%nx != 0)
    WARN_LEN;
  
  for (size_t i=0; i<dimprod; i++)
    DATA(ret)[i] = pow(DATA(x)[i%nx], DATA(y)[i]);
  
  return ret;
}

static inline matrix_t* pow_vecvec(const matrix_t *const restrict x, const matrix_t *const restrict y)
{
  const size_t nx = (size_t) NROWS(x)*NCOLS(x);
  const size_t ny = (size_t) NROWS(y)*NCOLS(y);
  const size_t nret = MAX(nx, ny);
  matrix_t *ret;
  
  if ((nx > ny && nx%ny != 0) || (nx < ny && ny%nx != 0))
    WARN_LEN;
  
  ret = newvec(nret);
  
  for (size_t i=0; i<nret; i++)
    DATA(ret)[i] = pow(DATA(x)[i%nx], DATA(y)[i%ny]);
  
  return ret;
}



SEXP R_pow_spm(SEXP x_ptr, SEXP y_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  matrix_t *y = (matrix_t*) getRptr(y_ptr);
  
  matrix_t *ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      ret = pow_vecvec(x, y);
    else
      ret = pow_vecmat(x, y);
  }
  else
  {
    if (ISAVEC(y))
      ret = pow_matvec(x, y);
    else
      ret = pow_matmat(x, y);
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
