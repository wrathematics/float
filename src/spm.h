#ifndef SPM_H_
#define SPM_H_


#include <R.h>
#include <Rinternals.h>

#include "types.h"

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

#define newRptr(ptr,Rptr,fin) PROTECT(Rptr = R_MakeExternalPtr(ptr, R_NilValue, R_NilValue));R_RegisterCFinalizerEx(Rptr, fin, TRUE)
#define getRptr(ptr) R_ExternalPtrAddr(ptr);

static inline void matfin(SEXP ptr)
{
  matrix_t *x;
  if (NULL == R_ExternalPtrAddr(ptr))
    return;
  
  x = (matrix_t*) R_ExternalPtrAddr(ptr);
  freemat(x);
  R_ClearExternalPtr(ptr);
}


#endif
