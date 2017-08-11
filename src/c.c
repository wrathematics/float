#include <Rdefines.h>

#include "spm.h"


SEXP R_c_spm(SEXP x_ptr, SEXP additional)
{
  SEXP ret_ptr;
  size_t len;
  
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  len = (size_t)NROWS(x) * NCOLS(x);
  
  for (int i=0; i<LENGTH(additional); i++)
  {
    SEXP tmp = GET_SLOT(VECTOR_ELT(additional, i), install("ptr"));
    x = (matrix_t*) getRptr(tmp);
    len += (size_t) NROWS(x) * NCOLS(x);
  }
  
  // TODO check for overflow
  
  matrix_t *ret = newvec((int)len);
  newRptr(ret, ret_ptr, matfin);
  size_t sofar = 0;
  
  x = (matrix_t*) getRptr(x_ptr);
  memcpy(DATA(ret), DATA(x), NROWS(x) * NCOLS(x) * sizeof(float));
  sofar = NROWS(x) * NCOLS(x);
  
  for (int i=0; i<LENGTH(additional); i++)
  {
    SEXP tmp = GET_SLOT(VECTOR_ELT(additional, i), install("ptr"));
    x = (matrix_t*) getRptr(tmp);
    memcpy(DATA(ret) + sofar, DATA(x), NROWS(x) * NCOLS(x) * sizeof(float));
    sofar += NROWS(x) * NCOLS(x);
  }
  
  
  UNPROTECT(1);
  return ret_ptr;
}
