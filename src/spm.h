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

#endif
