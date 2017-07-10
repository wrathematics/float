#include "spm.h"


#define INT(x,i) INTEGER(x)[i]

// assume positive integer indices for now
SEXP R_bracket_spm(SEXP x_ptr, SEXP I, SEXP J)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int mx = NROWS(x);
  
  const int m = LENGTH(I);
  const int n = LENGTH(J);
  matrix_t *ret = newmat(m, n);
  ISAVEC(ret) = ISAVEC(x);
  
  for (int j=0; j<n; j++)
  {
    const int mJ_j = mx*(INT(J, j) - 1);
    for (int i=0; i<m; i++)
      DATA(ret)[i + m*j] = DATA(x)[INT(I, i)-1 + mJ_j];
  }
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
