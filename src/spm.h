#ifndef SPM_H_
#define SPM_H_


#if (defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER))
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
#endif



#include <R.h>
#include <Rinternals.h>

#include "cdefs.h"
#include "types.h"


extern float NA_FLOAT;

#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))

static inline matrix_t* getRptr_safe(void *ptr)
{
  if (ptr == NULL)
    error("invalid spm object; pointer is NULL");
  
  return (matrix_t*)R_ExternalPtrAddr(ptr);
}

#define newRptr(ptr,Rptr,fin) PROTECT(Rptr = R_MakeExternalPtr(ptr, R_NilValue, R_NilValue));R_RegisterCFinalizerEx(Rptr, fin, TRUE)
#define getRptr(ptr) getRptr_safe(ptr)

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
