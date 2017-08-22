#include "spm.h"

#define INT(x,i) INTEGER(x)[i]

// assume positive integer indices for now
SEXP R_bracket_spm(SEXP x_ptr, SEXP I, SEXP J, SEXP drop)
{
  SEXP ret_ptr;
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const len_t mx = NROWS(x);
  const int m = LENGTH(I);
  const int n = LENGTH(J);
  matrix_t *ret;
  
  if (!ISAVEC(x) && INTEGER(drop)[0] && (m == 1 || n == 1))
  {
    if (m == 1)
    {
      ret = newvec(n);
      for (int j=0; j<n; j++)
        DATA(ret)[j] = DATA(x)[INT(I, 0)-1 + mx*(INT(J, j)-1)];
    }
    else
    {
      ret = newvec(m);
      for (int i=0; i<n; i++)
        DATA(ret)[i] = DATA(x)[INT(I, i)-1 + mx*(INT(J, 0)-1)];
    }
  }
  else
  {
    ret = newmat(m, n);
    ISAVEC(ret) = ISAVEC(x);
    
    for (int j=0; j<n; j++)
    {
      const int mJ_j = mx*(INT(J, j) - 1);
      for (int i=0; i<m; i++)
        DATA(ret)[i + m*j] = DATA(x)[INT(I, i)-1 + mJ_j];
    }
  }
  
  
  newRptr(ret, ret_ptr, matfin);
  UNPROTECT(1);
  return ret_ptr;
}
