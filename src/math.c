#include <math.h>

#include "NA.h"
#include "Rfloat.h"
#include "unroll.h"


#define FUN_INIT \
  SEXP ret; \
  const float_len_t m = (float_len_t) NROWS(x); \
  const float_len_t n = (float_len_t) NCOLS(x); \
   \
  if (ISAVEC(x)) \
    PROTECT(ret = newvec((R_xlen_t)m*n)); \
  else \
    PROTECT(ret = newmat(m, n));

#define APPLY(fun) \
  float *xf = FLOAT(x); \
  float *retf = FLOAT(ret); \
  for (size_t i=0; i<((size_t)m*n); i++) \
    retf[i] = fun(xf[i]);

#define FUN_END \
  UNPROTECT(1); \
  return ret;

#define MATHFUN(fun) \
  FUN_INIT \
  APPLY(fun) \
  FUN_END


// ----------------------------------------------------------------------------
// logs
// ----------------------------------------------------------------------------

SEXP R_exp_spm(SEXP x)
{
  MATHFUN(expf)
}

SEXP R_expm1_spm(SEXP x)
{
  MATHFUN(expm1f)
}

SEXP R_log_spm(SEXP x, SEXP base_)
{
  FUN_INIT
  
  float *xf = FLOAT(x);
  float *retf = FLOAT(ret);
  
  const float invlogbase = 1.0f / logf(REAL(base_)[0]);
  
  for (size_t i=0; i<((size_t)m*n); i++)
    retf[i] = logf(xf[i]) * invlogbase;
  
  FUN_END
}

SEXP R_log10_spm(SEXP x)
{
  MATHFUN(log10f)
}

SEXP R_log2_spm(SEXP x)
{
  MATHFUN(log2f)
}



// ----------------------------------------------------------------------------
// trig
// ----------------------------------------------------------------------------

SEXP R_sin_spm(SEXP x)
{
  MATHFUN(sinf)
}

SEXP R_cos_spm(SEXP x)
{
  MATHFUN(cosf)
}

SEXP R_tan_spm(SEXP x)
{
  MATHFUN(tanf)
}

SEXP R_asin_spm(SEXP x)
{
  MATHFUN(asinf)
}

SEXP R_acos_spm(SEXP x)
{
  MATHFUN(acosf)
}

SEXP R_atan_spm(SEXP x)
{
  MATHFUN(atanf)
}



// ----------------------------------------------------------------------------
// hyperbolic
// ----------------------------------------------------------------------------

SEXP R_sinh_spm(SEXP x)
{
  MATHFUN(sinhf)
}

SEXP R_cosh_spm(SEXP x)
{
  MATHFUN(coshf)
}

SEXP R_tanh_spm(SEXP x)
{
  MATHFUN(tanhf)
}

SEXP R_asinh_spm(SEXP x)
{
  MATHFUN(asinhf)
}

SEXP R_acosh_spm(SEXP x)
{
  MATHFUN(acoshf)
}

SEXP R_atanh_spm(SEXP x)
{
  MATHFUN(atanhf)
}



// ----------------------------------------------------------------------------
// misc
// ----------------------------------------------------------------------------

SEXP R_abs_spm(SEXP x)
{
  MATHFUN(fabsf)
}

SEXP R_sqrt_spm(SEXP x)
{
  MATHFUN(sqrtf)
}



// ----------------------------------------------------------------------------
// special
// ----------------------------------------------------------------------------

SEXP R_gamma_spm(SEXP x)
{
  MATHFUN(tgammaf)
}

SEXP R_lgamma_spm(SEXP x)
{
  MATHFUN(lgammaf)
}



// ----------------------------------------------------------------------------
// mathis
// ----------------------------------------------------------------------------

SEXP R_isfinite_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  float *xf = FLOAT(x);
  int *reti = LOGICAL(ret);
  
  for (float_len_t j=0; j<n; j++)
  {
    for (float_len_t i=0; i<m; i++)
    {
      const float tmp =  xf[i + m*j];
      reti[i + m*j] = !isinf(tmp) && !isnan(tmp);
    }
  }
  
  UNPROTECT(1);
  return ret;
}

SEXP R_isinfinite_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  float *xf = FLOAT(x);
  int *reti = LOGICAL(ret);
  
  for (float_len_t j=0; j<n; j++)
  {
    for (float_len_t i=0; i<m; i++)
    {
      const float tmp =  xf[i + m*j];
      reti[i + m*j] = abs(isinf(tmp));
    }
  }
  
  UNPROTECT(1);
  return ret;
}

SEXP R_isnan_spm(SEXP x)
{
  SEXP ret;
  const float_len_t m = (float_len_t) NROWS(x);
  const float_len_t n = (float_len_t) NCOLS(x);
  
  if (ISAVEC(x))
    PROTECT(ret = allocVector(LGLSXP, ((size_t)m*n)));
  else
    PROTECT(ret = allocMatrix(LGLSXP, m, n));
  
  float *xf = FLOAT(x);
  int *reti = LOGICAL(ret);
  
  for (float_len_t j=0; j<n; j++)
  {
    for (float_len_t i=0; i<m; i++)
    {
      const float tmp = xf[i + m*j];
      reti[i + m*j] = ISNANf(tmp);
    }
  }
  
  UNPROTECT(1);
  return ret;
}



// ----------------------------------------------------------------------------
// rounding
// ----------------------------------------------------------------------------

SEXP R_ceiling_spm(SEXP x)
{
  MATHFUN(ceilf)
}

SEXP R_floor_spm(SEXP x)
{
  MATHFUN(floorf)
}

SEXP R_trunc_spm(SEXP x)
{
  MATHFUN(roundf)
}

// NOTE I'm not sure if this is numerically wise...
static inline float roundfun(const float x, const float p)
{
  return roundf(x*p)/p;
}

SEXP R_round_spm(SEXP x, SEXP digits)
{
  FUN_INIT
  
  float *xf = FLOAT(x);
  float *retf = FLOAT(ret);
  
  const float p = powf(10, REAL(digits)[0]);
  for (size_t i=0; i<((size_t)m*n); i++)
    retf[i] = roundfun(xf[i], p);
  
  FUN_END
}
