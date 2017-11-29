# -----------------------------------------------------------------------------
# logs
# -----------------------------------------------------------------------------

#' Logarithms and Exponentials
#' 
#' exp/log functions.
#' 
#' @param x
#' A float vector/matrix.
#' @param base
#' The logarithm base.
#' 
#' @return
#' A float vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = flrunif(10)
#' log(x)
#' }
#' 
#' @name log
#' @rdname log
NULL



exp_float32 = function(x)
{
  ret = .Call(R_exp_spm, DATA(x))
  float32(ret)
}

expm1_float32 = function(x)
{
  ret = .Call(R_expm1_spm, DATA(x))
  float32(ret)
}

log_float32 = function(x, base=exp(1))
{
  if (is.float(base))
    base = dbl(base[1])
  
  ret = .Call(R_log_spm, DATA(x), as.double(base))
  float32(ret)
}

log10_float32 = function(x)
{
  ret = .Call(R_log10_spm, DATA(x))
  float32(ret)
}

log2_float32 = function(x)
{
  ret = .Call(R_log2_spm, DATA(x))
  float32(ret)
}



#' @rdname log
#' @export
setMethod("exp", signature(x="float32"), exp_float32)

#' @rdname log
#' @export
setMethod("expm1", signature(x="float32"), expm1_float32)

#' @rdname log
#' @export
setMethod("log", signature(x="float32"), log_float32)

#' @rdname log
#' @export
setMethod("log10", signature(x="float32"), log10_float32)

#' @rdname log
#' @export
setMethod("log2", signature(x="float32"), log2_float32)



# -----------------------------------------------------------------------------
# trig
# -----------------------------------------------------------------------------

#' Trigonometric functions
#' 
#' Basic trig functions.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' A float vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = flrunif(10)
#' sin(x)
#' }
#' 
#' @name trig
#' @rdname trig
NULL



sin_float32 = function(x)
{
  ret = .Call(R_sin_spm, DATA(x))
  float32(ret)
}

cos_float32 = function(x)
{
  ret = .Call(R_cos_spm, DATA(x))
  float32(ret)
}

tan_float32 = function(x)
{
  ret = .Call(R_tan_spm, DATA(x))
  float32(ret)
}

asin_float32 = function(x)
{
  ret = .Call(R_asin_spm, DATA(x))
  float32(ret)
}

acos_float32 = function(x)
{
  ret = .Call(R_acos_spm, DATA(x))
  float32(ret)
}

atan_float32 = function(x)
{
  ret = .Call(R_atan_spm, DATA(x))
  float32(ret)
}



#' @rdname trig
#' @export
setMethod("sin", signature(x="float32"), sin_float32)

#' @rdname trig
#' @export
setMethod("cos", signature(x="float32"), cos_float32)

#' @rdname trig
#' @export
setMethod("tan", signature(x="float32"), tan_float32)

#' @rdname trig
#' @export
setMethod("asin", signature(x="float32"), asin_float32)

#' @rdname trig
#' @export
setMethod("acos", signature(x="float32"), acos_float32)

#' @rdname trig
#' @export
setMethod("atan", signature(x="float32"), atan_float32)



# -----------------------------------------------------------------------------
# hyperbolic
# -----------------------------------------------------------------------------

#' Hyperbolic functions
#' 
#' Hyperbolic functions.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' A float vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = flrunif(10)
#' sinh(x)
#' }
#' 
#' @name hyperbolic
#' @rdname hyperbolic
NULL



sinh_float32 = function(x)
{
  ret = .Call(R_sinh_spm, DATA(x))
  float32(ret)
}

cosh_float32 = function(x)
{
  ret = .Call(R_cosh_spm, DATA(x))
  float32(ret)
}

tanh_float32 = function(x)
{
  ret = .Call(R_tanh_spm, DATA(x))
  float32(ret)
}

asinh_float32 = function(x)
{
  ret = .Call(R_asinh_spm, DATA(x))
  float32(ret)
}

acosh_float32 = function(x)
{
  ret = .Call(R_acosh_spm, DATA(x))
  float32(ret)
}

atanh_float32 = function(x)
{
  ret = .Call(R_atanh_spm, DATA(x))
  float32(ret)
}



#' @rdname hyperbolic
#' @export
setMethod("sinh", signature(x="float32"), sinh_float32)

#' @rdname hyperbolic
#' @export
setMethod("cosh", signature(x="float32"), cosh_float32)

#' @rdname hyperbolic
#' @export
setMethod("tanh", signature(x="float32"), tanh_float32)

#' @rdname hyperbolic
#' @export
setMethod("asinh", signature(x="float32"), asinh_float32)

#' @rdname hyperbolic
#' @export
setMethod("acosh", signature(x="float32"), acosh_float32)

#' @rdname hyperbolic
#' @export
setMethod("atanh", signature(x="float32"), atanh_float32)



# -----------------------------------------------------------------------------
# misc
# -----------------------------------------------------------------------------

#' Miscellaneous mathematical functions
#' 
#' Miscellaneous mathematical functions.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' A float vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = flrunif(10)
#' sqrt(x)
#' }
#' 
#' @name miscmath
#' @rdname miscmath
NULL



abs_float32 = function(x)
{
  ret = .Call(R_abs_spm, DATA(x))
  float32(ret)
}

sqrt_float32 = function(x)
{
  ret = .Call(R_sqrt_spm, DATA(x))
  float32(ret)
}



#' @rdname miscmath
#' @export
setMethod("abs", signature(x="float32"), abs_float32)

#' @rdname miscmath
#' @export
setMethod("sqrt", signature(x="float32"), sqrt_float32)



# -----------------------------------------------------------------------------
# special
# -----------------------------------------------------------------------------

#' Special mathematical functions
#' 
#' Special mathematical functions.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' A float vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = flrunif(10)
#' lgamma(x)
#' }
#' 
#' @name specialmath
#' @rdname specialmath
NULL



gamma_float32 = function(x)
{
  ret = .Call(R_gamma_spm, DATA(x))
  float32(ret)
}

lgamma_float32 = function(x)
{
  ret = .Call(R_lgamma_spm, DATA(x))
  float32(ret)
}



#' @rdname specialmath
#' @export
setMethod("gamma", signature(x="float32"), gamma_float32)

#' @rdname specialmath
#' @export
setMethod("lgamma", signature(x="float32"), lgamma_float32)



# -----------------------------------------------------------------------------
# mathis
# -----------------------------------------------------------------------------

#' Finite, infinite, and NaNs
#' 
#' Finite, infinite, and NaNs.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' An integer vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = flrnorm(10)
#' is.nan(sqrt(x))
#' }
#' 
#' @name mathis
#' @rdname mathis
NULL



is.finite_float32 = function(x)
{
  .Call(R_isfinite_spm, DATA(x))
}

is.infinite_float32 = function(x)
{
  .Call(R_isinfinite_spm, DATA(x))
}

is.nan_float32 = function(x)
{
  .Call(R_isnan_spm, DATA(x))
}



#' @rdname mathis
#' @export
setMethod("is.finite", signature(x="float32"), is.finite_float32)

#' @rdname mathis
#' @export
setMethod("is.infinite", signature(x="float32"), is.infinite_float32)

#' @rdname mathis
#' @export
setMethod("is.nan", signature(x="float32"), is.nan_float32)



# -----------------------------------------------------------------------------
# rounding
# -----------------------------------------------------------------------------

#' Round
#' 
#' Rounding functions.
#' 
#' @param x
#' A float vector/matrix.
#' @param digits
#' The number of digits to use in rounding.
#' @param ...
#' ignored
#' 
#' @return
#' A float vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' library(float)
#' 
#' x = flrnorm(10)
#' floor(x)
#' 
#' @name round
#' @rdname round
NULL



ceiling_float32 = function(x)
{
  ret = .Call(R_ceiling_spm, DATA(x))
  float32(ret)
}

floor_float32 = function(x)
{
  ret = .Call(R_floor_spm, DATA(x))
  float32(ret)
}

trunc_float32 = function(x, ...)
{
  ret = .Call(R_trunc_spm, DATA(x))
  float32(ret)
}

round_float32 = function(x, digits=0)
{
  ret = .Call(R_round_spm, DATA(x), as.double(digits))
  float32(ret)
}



#' @rdname round
#' @export
setMethod("ceiling", signature(x="float32"), ceiling_float32)

#' @rdname round
#' @export
setMethod("floor", signature(x="float32"), floor_float32)

#' @rdname round
#' @export
setMethod("trunc", signature(x="float32"), trunc_float32)

#' @rdname round
#' @export
setMethod("round", signature(x="float32"), round_float32)
