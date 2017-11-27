#ifndef SPM_H_
#define SPM_H_


#include <R.h>
#include <Rinternals.h>

#include "cdefs.h"
#include "types.h"

extern float NA_FLOAT;

#define INT(x) (INTEGER(x)[0])
#define LGL(x) (LOGICAL(x)[0])
#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))


#endif
