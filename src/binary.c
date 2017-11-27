#include <math.h>

#include "NA.h"
#include "Rfloat.h"
#include "unroll.h"


#define ERR_NONC error("non-conformable arrays")
#define ERR_DIMS(dimprod,nr) error("dims [product %zu] do not match the length of object [%d]\n", dimprod, nr)
#define WARN_LEN warning("longer object length is not a multiple of shorter object length\n")

#define BINOP_MATMAT(x,y,FUN) \
  SEXP ret; \
  const len_t m = NROWS(x); \
  const len_t n = NCOLS(x); \
  if (m != NROWS(y) || n != NCOLS(y)) \
    ERR_NONC; \
  \
  PROTECT(ret = newmat(m, n)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  float *retf = FLOAT(ret); \
  \
  for (len_t j=0; j<n; j++) \
  { \
    for (len_t i=0; i<m; i++) \
      retf[i + m*j] = xf[i + m*j] FUN yf[i + m*j]; \
  } \
  \
  UNPROTECT(1); \
  return ret;

#define BINOP_MATVEC(x,y,FUN) \
  SEXP ret; \
  const len_t m = NROWS(x); \
  const len_t n = NCOLS(x); \
  const size_t ny = NROWS(y); \
  const size_t dimprod = (size_t)m*n; \
  PROTECT(ret = newmat(m, n)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  float *retf = FLOAT(ret); \
  \
  if (dimprod < ny) \
    ERR_DIMS(dimprod, NROWS(y)); \
  else if (dimprod%ny != 0) \
    WARN_LEN; \
  \
  for (size_t i=0; i<dimprod; i++) \
    retf[i] = xf[i] FUN yf[i%ny]; \
  \
  UNPROTECT(1); \
  return ret;

#define BINOP_VECMAT(x,y,FUN) \
  SEXP ret; \
  const len_t m = NROWS(y); \
  const len_t n = NCOLS(y); \
  const size_t nx = NROWS(x); \
  const size_t dimprod = (size_t)m*n; \
  PROTECT(ret = newmat(m, n)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  float *retf = FLOAT(ret); \
  \
  if (dimprod < nx) \
    ERR_DIMS(dimprod, NROWS(x)); \
  else if (dimprod%nx != 0) \
    WARN_LEN; \
  \
  for (size_t i=0; i<dimprod; i++) \
    retf[i] = xf[i%nx] FUN yf[i]; \
  \
  UNPROTECT(1); \
  return ret;

#define BINOP_VECVEC(x,y,FUN) \
  SEXP ret; \
  const size_t nx = (size_t) NROWS(x)*NCOLS(x); \
  const size_t ny = (size_t) NROWS(y)*NCOLS(y); \
  const size_t nret = MAX(nx, ny); \
  \
  if ((nx > ny && nx%ny != 0) || (nx < ny && ny%nx != 0)) \
    WARN_LEN; \
  \
  PROTECT(ret = newvec(nret)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  float *retf = FLOAT(ret); \
  \
  for (size_t i=0; i<nret; i++) \
    retf[i] = xf[i%nx] FUN yf[i%ny]; \
  \
  UNPROTECT(1); \
  return ret;



#define COMPARE_MATMAT(x,y,FUN) \
  const len_t m = NROWS(x); \
  const len_t n = NCOLS(x); \
  if (m != NROWS(y) || n != NCOLS(y)) \
    ERR_NONC; \
  \
  SEXP ret; \
  PROTECT(ret = allocMatrix(LGLSXP, m, n)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  \
  for (len_t j=0; j<n; j++) \
  { \
    for (len_t i=0; i<m; i++) \
    { \
      const float tmp1 = xf[i + m*j]; \
      const float tmp2 = yf[i + m*j]; \
      if (ISNAf(tmp1) ||  isnan(tmp1) || ISNAf(tmp2) ||  isnan(tmp2)) \
        LOGICAL(ret)[i + m*j] = NA_LOGICAL; \
      else \
        LOGICAL(ret)[i + m*j] = tmp1 FUN tmp2; \
    } \
  } \
  \
  UNPROTECT(1); \
  return ret;

#define COMPARE_MATVEC(x,y,FUN) \
  const len_t m = NROWS(x); \
  const len_t n = NCOLS(x); \
  const size_t ny = NROWS(y); \
  const size_t dimprod = (size_t)m*n; \
  SEXP ret; \
  PROTECT(ret = allocMatrix(LGLSXP, m, n)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  \
  if (dimprod < ny) \
    ERR_DIMS(dimprod, NROWS(y)); \
  else if (dimprod%ny != 0) \
    WARN_LEN; \
  \
  for (size_t i=0; i<dimprod; i++) \
  { \
    const float tmp1 = xf[i]; \
    const float tmp2 = yf[i%ny]; \
    if (ISNAf(tmp1) ||  isnan(tmp1) || ISNAf(tmp2) ||  isnan(tmp2)) \
      LOGICAL(ret)[i] = NA_LOGICAL; \
    else \
      LOGICAL(ret)[i] = tmp1 FUN tmp2; \
  } \
  \
  UNPROTECT(1); \
  return ret;

#define COMPARE_VECMAT(x,y,FUN) \
  const len_t m = NROWS(y); \
  const len_t n = NCOLS(y); \
  const size_t nx = NROWS(x); \
  const size_t dimprod = (size_t)m*n; \
  SEXP ret; \
  PROTECT(ret = allocMatrix(LGLSXP, m, n)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  \
  if (dimprod < nx) \
    ERR_DIMS(dimprod, NROWS(x)); \
  else if (dimprod%nx != 0) \
    WARN_LEN; \
  \
  for (size_t i=0; i<dimprod; i++) \
  { \
    const float tmp1 = xf[i%nx]; \
    const float tmp2 = yf[i]; \
    if (ISNAf(tmp1) ||  isnan(tmp1) || ISNAf(tmp2) ||  isnan(tmp2)) \
      LOGICAL(ret)[i] = NA_LOGICAL; \
    else \
      LOGICAL(ret)[i] = tmp1 FUN tmp2; \
  } \
  \
  UNPROTECT(1); \
  return ret;

#define COMPARE_VECVEC(x,y,FUN) \
  const size_t nx = (size_t) NROWS(x)*NCOLS(x); \
  const size_t ny = (size_t) NROWS(y)*NCOLS(y); \
  const size_t nret = MAX(nx, ny); \
  SEXP ret; \
  \
  if ((nx > ny && nx%ny != 0) || (nx < ny && ny%nx != 0)) \
    WARN_LEN; \
  \
  PROTECT(ret = allocVector(LGLSXP, nret)); \
  float *xf = FLOAT(x); \
  float *yf = FLOAT(y); \
  \
  for (size_t i=0; i<nret; i++) \
  { \
    const float tmp1 = xf[i%nx]; \
    const float tmp2 = yf[i%ny]; \
    if (ISNAf(tmp1) ||  isnan(tmp1) || ISNAf(tmp2) ||  isnan(tmp2)) \
      LOGICAL(ret)[i] = NA_LOGICAL; \
    else \
      LOGICAL(ret)[i] = tmp1 FUN tmp2; \
  } \
  \
  UNPROTECT(1); \
  return ret;



// ----------------------------------------------------------------------------
// Arithmetic
// ----------------------------------------------------------------------------

// +
static inline SEXP add_matmat(SEXP x, SEXP y)
{
  BINOP_MATMAT(x, y, +);
}

static inline SEXP add_matvec(SEXP x, SEXP y)
{
  BINOP_MATVEC(x, y, +);
}

static inline SEXP add_vecvec(SEXP x, SEXP y)
{
  BINOP_VECVEC(x, y, +);
}

SEXP R_add_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = add_vecvec(x, y));
    else
      PROTECT(ret = add_matvec(y, x));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = add_matvec(x, y));
    else
      PROTECT(ret = add_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}




// *
static inline SEXP mul_matmat(SEXP x, SEXP y)
{
  BINOP_MATMAT(x, y, *);
}

static inline SEXP mul_matvec(SEXP x, SEXP y)
{
  BINOP_MATVEC(x, y, *);
}

static inline SEXP mul_vecvec(SEXP x, SEXP y)
{
  BINOP_VECVEC(x, y, *);
}

SEXP R_mul_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = mul_vecvec(x, y));
    else
      PROTECT(ret = mul_matvec(y, x));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = mul_matvec(x, y));
    else
      PROTECT(ret = mul_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}



// -
static inline SEXP sub_matmat(SEXP x, SEXP y)
{
  BINOP_MATMAT(x, y, -);
}

static inline SEXP sub_matvec(SEXP x, SEXP y)
{
  BINOP_MATVEC(x, y, -);
}

static inline SEXP sub_vecmat(SEXP x, SEXP y)
{
  BINOP_VECMAT(x, y, -);
}

static inline SEXP sub_vecvec(SEXP x, SEXP y)
{
  BINOP_VECVEC(x, y, -);
}

SEXP R_sub_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = sub_vecvec(x, y));
    else
      PROTECT(ret = sub_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = sub_matvec(x, y));
    else
      PROTECT(ret = sub_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}




// /
static inline SEXP div_matmat(SEXP x, SEXP y)
{
  BINOP_MATMAT(x, y, /);
}

static inline SEXP div_matvec(SEXP x, SEXP y)
{
  BINOP_MATVEC(x, y, /);
}

static inline SEXP div_vecmat(SEXP x, SEXP y)
{
  BINOP_VECMAT(x, y, /);
}

static inline SEXP div_vecvec(SEXP x, SEXP y)
{
  BINOP_VECVEC(x, y, /);
}

SEXP R_div_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = div_vecvec(x, y));
    else
      PROTECT(ret = div_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = div_matvec(x, y));
    else
      PROTECT(ret = div_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}



// ^
static inline SEXP pow_matmat(SEXP x, SEXP y)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  if (m != NROWS(y) || n != NCOLS(y))
    ERR_NONC;
  
  PROTECT(ret = newmat(m, n));
  float *xf = FLOAT(x);
  float *yf = FLOAT(y);
  float *retf = FLOAT(ret);
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
      retf[i + m*j] = pow(xf[i + m*j], yf[i + m*j]);
  }
  
  UNPROTECT(1);
  return ret;
}

static inline SEXP pow_matvec(SEXP x, SEXP y)
{
  SEXP ret;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const size_t ny = NROWS(y);
  const size_t dimprod = (size_t)m*n;
  PROTECT(ret = newmat(m, n));
  float *xf = FLOAT(x);
  float *yf = FLOAT(y);
  float *retf = FLOAT(ret);
  
  if (dimprod < ny)
    ERR_DIMS(dimprod, NROWS(y));
  else if (dimprod%ny != 0)
    WARN_LEN;
  
  for (size_t i=0; i<dimprod; i++)
    retf[i] = pow(xf[i], yf[i%ny]);
  
  UNPROTECT(1);
  return ret;
}

static inline SEXP pow_vecmat(SEXP x, SEXP y)
{
  SEXP ret;
  const len_t m = NROWS(y);
  const len_t n = NCOLS(y);
  const size_t nx = NROWS(x);
  const size_t dimprod = (size_t)m*n;
  PROTECT(ret = newmat(m, n));
  float *xf = FLOAT(x);
  float *yf = FLOAT(y);
  float *retf = FLOAT(ret);
  
  if (dimprod < nx)
    ERR_DIMS(dimprod, NROWS(x));
  else if (dimprod%nx != 0)
    WARN_LEN;
  
  for (size_t i=0; i<dimprod; i++)
    retf[i] = pow(xf[i%nx], yf[i]);
  
  UNPROTECT(1);
  return ret;
}

static inline SEXP pow_vecvec(SEXP x, SEXP y)
{
  SEXP ret;
  const size_t nx = (size_t) NROWS(x)*NCOLS(x);
  const size_t ny = (size_t) NROWS(y)*NCOLS(y);
  const size_t nret = MAX(nx, ny);
  
  if ((nx > ny && nx%ny != 0) || (nx < ny && ny%nx != 0))
    WARN_LEN;
  
  PROTECT(ret = newvec(nret));
  float *xf = FLOAT(x);
  float *yf = FLOAT(y);
  float *retf = FLOAT(ret);
  
  for (size_t i=0; i<nret; i++)
    retf[i] = pow(xf[i%nx], yf[i%ny]);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_pow_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = pow_vecvec(x, y));
    else
      PROTECT(ret = pow_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = pow_matvec(x, y));
    else
      PROTECT(ret = pow_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// Comparisons
// ----------------------------------------------------------------------------

// <
static inline SEXP lt_matmat(SEXP x, SEXP y)
{
  COMPARE_MATMAT(x, y, <);
}

static inline SEXP lt_matvec(SEXP x, SEXP y)
{
  COMPARE_MATVEC(x, y, <);
}

static inline SEXP lt_vecmat(SEXP x, SEXP y)
{
  COMPARE_VECMAT(x, y, <);
}

static inline SEXP lt_vecvec(SEXP x, SEXP y)
{
  COMPARE_VECVEC(x, y, <);
}

SEXP R_lt_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = lt_vecvec(x, y));
    else
      PROTECT(ret = lt_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = lt_matvec(x, y));
    else
      PROTECT(ret = lt_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}




// <=
static inline SEXP le_matmat(SEXP x, SEXP y)
{
  COMPARE_MATMAT(x, y, <=);
}

static inline SEXP le_matvec(SEXP x, SEXP y)
{
  COMPARE_MATVEC(x, y, <=);
}

static inline SEXP le_vecmat(SEXP x, SEXP y)
{
  COMPARE_VECMAT(x, y, <=);
}

static inline SEXP le_vecvec(SEXP x, SEXP y)
{
  COMPARE_VECVEC(x, y, <=);
}

SEXP R_le_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = le_vecvec(x, y));
    else
      PROTECT(ret = le_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = le_matvec(x, y));
    else
      PROTECT(ret = le_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}



// eq
static inline SEXP eq_matmat(SEXP x, SEXP y)
{
  COMPARE_MATMAT(x, y, ==);
}

static inline SEXP eq_matvec(SEXP x, SEXP y)
{
  COMPARE_MATVEC(x, y, ==);
}

static inline SEXP eq_vecmat(SEXP x, SEXP y)
{
  COMPARE_VECMAT(x, y, ==);
}

static inline SEXP eq_vecvec(SEXP x, SEXP y)
{
  COMPARE_VECVEC(x, y, ==);
}

SEXP R_eq_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = eq_vecvec(x, y));
    else
      PROTECT(ret = eq_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = eq_matvec(x, y));
    else
      PROTECT(ret = eq_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}




// >
static inline SEXP gt_matmat(SEXP x, SEXP y)
{
  COMPARE_MATMAT(x, y, >);
}

static inline SEXP gt_matvec(SEXP x, SEXP y)
{
  COMPARE_MATVEC(x, y, >);
}

static inline SEXP gt_vecmat(SEXP x, SEXP y)
{
  COMPARE_VECMAT(x, y, >);
}

static inline SEXP gt_vecvec(SEXP x, SEXP y)
{
  COMPARE_VECVEC(x, y, >);
}

SEXP R_gt_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = gt_vecvec(x, y));
    else
      PROTECT(ret = gt_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = gt_matvec(x, y));
    else
      PROTECT(ret = gt_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}



// >=
static inline SEXP ge_matmat(SEXP x, SEXP y)
{
  COMPARE_MATMAT(x, y, >=);
}

static inline SEXP ge_matvec(SEXP x, SEXP y)
{
  COMPARE_MATVEC(x, y, >=);
}

static inline SEXP ge_vecmat(SEXP x, SEXP y)
{
  COMPARE_VECMAT(x, y, >=);
}

static inline SEXP ge_vecvec(SEXP x, SEXP y)
{
  COMPARE_VECVEC(x, y, >=);
}

SEXP R_ge_spm(SEXP x, SEXP y)
{
  SEXP ret;
  
  if (ISAVEC(x))
  {
    if (ISAVEC(y))
      PROTECT(ret = ge_vecvec(x, y));
    else
      PROTECT(ret = ge_vecmat(x, y));
  }
  else
  {
    if (ISAVEC(y))
      PROTECT(ret = ge_matvec(x, y));
    else
      PROTECT(ret = ge_matmat(x, y));
  }
  
  UNPROTECT(1);
  return ret;
}
