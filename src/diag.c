#include "spm.h"


SEXP R_diag_spm(SEXP x_ptr)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  const int min = MIN(m, n);
  
  matrix_t *ret = newmat(min, 1);
  ISAVEC(ret) = true;
  
  for (int i=0; i<min; i++)
    DATA(ret)[i] = DATA(x)[i + m*i];
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}



SEXP R_diagmat_spm(SEXP x_ptr, SEXP nrow, SEXP ncol)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = INTEGER(nrow)[0];
  const int n = INTEGER(ncol)[0];
  const int len = NROWS(x);
  const int minmn = MIN(m, n);
  
  matrix_t *ret = newmat(m, n);
  ISAVEC(ret) = false;
  
  memset(DATA(ret), 0, m*n*sizeof(float));
  for (int i=0; i<minmn; i++)
    DATA(ret)[i + m*i] = DATA(x)[i%len];
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
