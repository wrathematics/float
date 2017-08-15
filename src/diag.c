#include "spm.h"


SEXP R_diag_spm(SEXP x_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const len_t min = MIN(m, n);
  
  matrix_t *ret = newvec(min);
  
  for (len_t i=0; i<min; i++)
    DATA(ret)[i] = DATA(x)[i + m*i];
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_diagmat_spm(SEXP x_ptr, SEXP nrow, SEXP ncol)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t m = INTEGER(nrow)[0];
  const len_t n = INTEGER(ncol)[0];
  const len_t len = NROWS(x);
  const len_t minmn = MIN(m, n);
  
  matrix_t *ret = newmat(m, n);
  
  memset(DATA(ret), 0, m*n*sizeof(float));
  for (len_t i=0; i<minmn; i++)
    DATA(ret)[i + m*i] = DATA(x)[i%len];
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
