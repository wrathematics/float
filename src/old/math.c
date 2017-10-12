#include <math.h>

#include "NA.h"
#include "spm.h"


#define FUN_INIT \
  SEXP ret_ptr; \
  matrix_t *x = (matrix_t*) getRptr(x_ptr); \
  const len_t m = NROWS(x); \
  const len_t n = NCOLS(x); \
   \
  matrix_t *ret = newmat(m, n); \
  ISAVEC(ret) = ISAVEC(x);

#define APPLY(fun) \
  for (size_t i=0; i<((size_t)m*n); i++) \
    DATA(ret)[i] = fun(DATA(x)[i]);

#define FUN_END \
  newRptr(ret, ret_ptr, matfin); \
  UNPROTECT(1); \
  return ret_ptr;

#define MATHFUN(fun) \
  FUN_INIT \
  APPLY(fun) \
  FUN_END


// ----------------------------------------------------------------------------
// logs
// ----------------------------------------------------------------------------

SEXP R_exp_spm(SEXP x_ptr)
{
  MATHFUN(expf)
}

SEXP R_expm1_spm(SEXP x_ptr)
{
  MATHFUN(expm1f)
}

SEXP R_log_spm(SEXP x_ptr, SEXP base_)
{
  FUN_INIT
  
  const float invlogbase = 1.0f / logf(REAL(base_)[0]);
  for (size_t i=0; i<((size_t)m*n); i++)
    DATA(ret)[i] = logf(DATA(x)[i]) * invlogbase;
  
  FUN_END
}

SEXP R_log10_spm(SEXP x_ptr)
{
  MATHFUN(log10f)
}

SEXP R_log2_spm(SEXP x_ptr)
{
  MATHFUN(log2f)
}



// ----------------------------------------------------------------------------
// trig
// ----------------------------------------------------------------------------

SEXP R_sin_spm(SEXP x_ptr)
{
  MATHFUN(sinf)
}

SEXP R_cos_spm(SEXP x_ptr)
{
  MATHFUN(cosf)
}

SEXP R_tan_spm(SEXP x_ptr)
{
  MATHFUN(tanf)
}

SEXP R_asin_spm(SEXP x_ptr)
{
  MATHFUN(asinf)
}

SEXP R_acos_spm(SEXP x_ptr)
{
  MATHFUN(acosf)
}

SEXP R_atan_spm(SEXP x_ptr)
{
  MATHFUN(atanf)
}



// ----------------------------------------------------------------------------
// hyperbolic
// ----------------------------------------------------------------------------

SEXP R_sinh_spm(SEXP x_ptr)
{
  MATHFUN(sinhf)
}

SEXP R_cosh_spm(SEXP x_ptr)
{
  MATHFUN(coshf)
}

SEXP R_tanh_spm(SEXP x_ptr)
{
  MATHFUN(tanhf)
}

SEXP R_asinh_spm(SEXP x_ptr)
{
  MATHFUN(asinhf)
}

SEXP R_acosh_spm(SEXP x_ptr)
{
  MATHFUN(acoshf)
}

SEXP R_atanh_spm(SEXP x_ptr)
{
  MATHFUN(atanhf)
}



// ----------------------------------------------------------------------------
// misc
// ----------------------------------------------------------------------------

SEXP R_abs_spm(SEXP x_ptr)
{
  MATHFUN(fabsf)
}

SEXP R_sqrt_spm(SEXP x_ptr)
{
  MATHFUN(sqrtf)
}



// ----------------------------------------------------------------------------
// special
// ----------------------------------------------------------------------------

SEXP R_gamma_spm(SEXP x_ptr)
{
  MATHFUN(tgammaf)
}

SEXP R_lgamma_spm(SEXP x_ptr)
{
  MATHFUN(lgammaf)
}



// ----------------------------------------------------------------------------
// mathis
// ----------------------------------------------------------------------------

SEXP R_isfinite_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
    {
      const float tmp =  DATA(x)[i + m*j];
      LOGICAL(ret)[i + m*j] = !isinf(tmp) && !isnanf(tmp);
    }
  }
  
  UNPROTECT(1);
  return ret;
}

SEXP R_isinfinite_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
    {
      const float tmp =  DATA(x)[i + m*j];
      LOGICAL(ret)[i + m*j] = isinff(tmp);
    }
  }
  
  UNPROTECT(1);
  return ret;
}

SEXP R_isnan_spm(SEXP x_ptr)
{
  SEXP ret;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<m; i++)
    {
      const float tmp = DATA(x)[i + m*j];
      LOGICAL(ret)[i + m*j] = ISNANf(tmp);
    }
  }
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// rounding
// ----------------------------------------------------------------------------

SEXP R_ceiling_spm(SEXP x_ptr)
{
  MATHFUN(ceilf)
}

SEXP R_floor_spm(SEXP x_ptr)
{
  MATHFUN(floorf)
}

SEXP R_trunc_spm(SEXP x_ptr)
{
  MATHFUN(roundf)
}

// NOTE I'm not sure if this is numerically wise...
static inline float roundfun(const float x, const float p)
{
  return roundf(x*p)/p;
}

SEXP R_round_spm(SEXP x_ptr, SEXP digits)
{
  FUN_INIT
  
  const float p = powf(10, REAL(digits)[0]);
  for (size_t i=0; i<((size_t)m*n); i++)
    DATA(ret)[i] = roundfun(DATA(x)[i], p);
  
  FUN_END
}
