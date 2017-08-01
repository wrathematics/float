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

#define FUN_END \
  newRptr(ret, ret_ptr, matfin); \
  UNPROTECT(1); \
  return ret_ptr;

// -----------------------------------------------------------------------------
// exp
// -----------------------------------------------------------------------------

SEXP R_exp_spm(SEXP x_ptr)
{
  FUN_INIT
  
  for (size_t i=0; i<((size_t)m*n); i++)
    DATA(ret)[i] = expf(DATA(x)[i]);
  
  FUN_END
}

SEXP R_expm1_spm(SEXP x_ptr)
{
  FUN_INIT
  
  for (size_t i=0; i<((size_t)m*n); i++)
    DATA(ret)[i] = expm1f(DATA(x)[i]);
  
  FUN_END
}



// -----------------------------------------------------------------------------
// log
// -----------------------------------------------------------------------------

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
  
  for (size_t i=0; i<((size_t)m*n); i++)
    DATA(ret)[i] = log10f(DATA(x)[i]);
  
  FUN_END
}

SEXP R_log2_spm(SEXP x_ptr)
{
  FUN_INIT
  
  for (size_t i=0; i<((size_t)m*n); i++)
    DATA(ret)[i] = log2f(DATA(x)[i]);
  
  FUN_END
}
