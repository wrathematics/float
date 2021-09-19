#ifndef R_FLOAT_PACKAGE_H_
#define R_FLOAT_PACKAGE_H_


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <float/float32.h>

#include <R.h>
#include <Rinternals.h>

extern float NA_FLOAT;

#define newmat(m, n) allocMatrix(INTSXP, m, n)
#define newvec(n) allocVector(INTSXP, n)

#define NROWS(x) (isMatrix(x) ? nrows(x) : XLENGTH(x))
#define NCOLS(x) (isMatrix(x) ? ncols(x) : 1)
#define ISAVEC(x) (!isMatrix(x))

#define INT(x) (INTEGER(x)[0])
#define LGL(x) (LOGICAL(x)[0])
#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define FLOAT(x) ((float*) INTEGER(x))
#define DATA(x) FLOAT(x)

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

#define FREE(ptr) if(ptr!=NULL) free(ptr)

#define BADMALLOC -1
#define THROW_MEMERR error("OOM")
#define CHECKMALLOC(ptr) if (ptr == NULL) THROW_MEMERR


#endif
