#include "spm.h"
#include <math.h>

#define FUN_INIT \
  SEXP ret_ptr; \
  matrix_t *x = (matrix_t*) getRptr(x_ptr); \
  const int m = NROWS(x); \
  const int n = NCOLS(x); \
   \
  matrix_t *ret = newmat(m, n); \
  ISAVEC(ret) = ISAVEC(x); \
  memcpy(DATA(ret), DATA(x), (size_t)m*n*sizeof(float));

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
