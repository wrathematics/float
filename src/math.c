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


// ----------------------------------------------------------------------------
// logs
// ----------------------------------------------------------------------------

SEXP R_exp_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(expf)
  FUN_END
}

SEXP R_expm1_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(expm1f)
  FUN_END
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
  FUN_INIT
  APPLY(log10f)
  FUN_END
}

SEXP R_log2_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(log2f)
  FUN_END
}



// ----------------------------------------------------------------------------
// trig
// ----------------------------------------------------------------------------

SEXP R_sin_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(sinf)
  FUN_END
}

SEXP R_cos_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(cosf)
  FUN_END
}

SEXP R_tan_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(tanf)
  FUN_END
}

SEXP R_asin_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(asinf)
  FUN_END
}

SEXP R_acos_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(acosf)
  FUN_END
}

SEXP R_atan_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(atanf)
  FUN_END
}



// ----------------------------------------------------------------------------
// hyperbolic
// ----------------------------------------------------------------------------

SEXP R_sinh_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(sinhf)
  FUN_END
}

SEXP R_cosh_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(coshf)
  FUN_END
}

SEXP R_tanh_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(tanhf)
  FUN_END
}

SEXP R_asinh_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(asinhf)
  FUN_END
}

SEXP R_acosh_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(acoshf)
  FUN_END
}

SEXP R_atanh_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(atanhf)
  FUN_END
}



// ----------------------------------------------------------------------------
// misc
// ----------------------------------------------------------------------------

SEXP R_abs_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(fabsf)
  FUN_END
}

SEXP R_sqrt_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(sqrtf)
  FUN_END
}



// ----------------------------------------------------------------------------
// special
// ----------------------------------------------------------------------------

SEXP R_gamma_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(tgammaf)
  FUN_END
}

SEXP R_lgamma_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(lgammaf)
  FUN_END
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
  FUN_INIT
  APPLY(ceilf)
  FUN_END
}

SEXP R_floor_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(floorf)
  FUN_END
}

SEXP R_trunc_spm(SEXP x_ptr)
{
  FUN_INIT
  APPLY(roundf)
  FUN_END
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
