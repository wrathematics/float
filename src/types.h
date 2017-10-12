#ifndef SPM_TYPES_
#define SPM_TYPES_


#include <R.h>
#include <Rinternals.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "cdefs.h"

#define FLOAT(x) ((float*) INTEGER(x))
#define DATA(x) FLOAT(x)
#define NROWS(x) (isMatrix(x) ? nrows(x) : LENGTH(x))
#define NCOLS(x) (isMatrix(x) ? ncols(x) : 1)
#define ISAVEC(x) (!isMatrix(x))

typedef int len_t;

#define newmat(m, n) allocMatrix(INTSXP, m, n)
#define newvec(n) allocVector(INTSXP, n)


#endif
