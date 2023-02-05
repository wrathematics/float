#include <float.h>

#include "Rfloat.h"


// we assume IEEE-754 compliance to build the package, so some values are hard-coded
SEXP R_machine_spm(void)
{
  int i;
  SEXP ret, ret_names;
  SEXP float_eps, float_xmin, float_xmax, float_base, float_digits,
    float_exponent, float_min_exp, float_max_exp;
  
  PROTECT(float_eps = allocVector(REALSXP, 1));
  REAL(float_eps)[0] = (double) FLT_EPSILON;
  
  PROTECT(float_xmin = allocVector(REALSXP, 1));
  REAL(float_xmin)[0] = (double) FLT_MIN;
  
  PROTECT(float_xmax = allocVector(REALSXP, 1));
  REAL(float_xmax)[0] = (double) FLT_MAX;
  
  PROTECT(float_base = allocVector(INTSXP, 1));
  INTEGER(float_base)[0] = (int) FLT_RADIX;
  
  PROTECT(float_digits = allocVector(INTSXP, 1));
  INTEGER(float_digits)[0] = (int) FLT_MANT_DIG;
  
  PROTECT(float_exponent = allocVector(INTSXP, 1));
  INTEGER(float_exponent)[0] = (int) 8;
  
  PROTECT(float_min_exp = allocVector(INTSXP, 1));
  INTEGER(float_min_exp)[0] = (int) FLT_MIN_EXP;
  
  PROTECT(float_max_exp = allocVector(INTSXP, 1));
  INTEGER(float_max_exp)[0] = (int) FLT_MAX_EXP;
  
  
  
  i = 0;
  PROTECT(ret_names = allocVector(STRSXP, 8));
  SET_STRING_ELT(ret_names, i++, mkChar("float.eps"));
  SET_STRING_ELT(ret_names, i++, mkChar("float.xmin"));
  SET_STRING_ELT(ret_names, i++, mkChar("float.xmax"));
  SET_STRING_ELT(ret_names, i++, mkChar("float.base"));
  SET_STRING_ELT(ret_names, i++, mkChar("float.digits"));
  SET_STRING_ELT(ret_names, i++, mkChar("float.exponent"));
  SET_STRING_ELT(ret_names, i++, mkChar("float.min.exp"));
  SET_STRING_ELT(ret_names, i++, mkChar("float.max.exp"));
  
  i = 0;
  PROTECT(ret = allocVector(VECSXP, 8));
  SET_VECTOR_ELT(ret, i++, float_eps);
  SET_VECTOR_ELT(ret, i++, float_xmin);
  SET_VECTOR_ELT(ret, i++, float_xmax);
  SET_VECTOR_ELT(ret, i++, float_base);
  SET_VECTOR_ELT(ret, i++, float_digits);
  SET_VECTOR_ELT(ret, i++, float_exponent);
  SET_VECTOR_ELT(ret, i++, float_min_exp);
  SET_VECTOR_ELT(ret, i++, float_max_exp);
  
  setAttrib(ret, R_NamesSymbol, ret_names);
    
  UNPROTECT(10);
  return ret;
}
