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
#' library(spm)
#' 
#' x = flrunif(10)
#' log(x)
#' }
#' 
#' @name log
#' @rdname log
NULL



exp.spm = function(x)
{
  ptr = .Call(R_exp_spm, x@ptr)
  new("spm", ptr=ptr)
}

expm1.spm = function(x)
{
  ptr = .Call(R_expm1_spm, x@ptr)
  new("spm", ptr=ptr)
}

log.spm = function(x, base=exp(1))
{
  if (is.spm(base))
    base = dbl(base[1])
  
  ptr = .Call(R_log_spm, x@ptr, as.double(base))
  new("spm", ptr=ptr)
}

log10.spm = function(x)
{
  ptr = .Call(R_log10_spm, x@ptr)
  new("spm", ptr=ptr)
}

log2.spm = function(x)
{
  ptr = .Call(R_log2_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @rdname log
#' @export
setMethod("exp", signature(x="spm"), exp.spm)

#' @rdname log
#' @export
setMethod("expm1", signature(x="spm"), expm1.spm)

#' @rdname log
#' @export
setMethod("log", signature(x="spm"), log.spm)

#' @rdname log
#' @export
setMethod("log10", signature(x="spm"), log10.spm)

#' @rdname log
#' @export
setMethod("log2", signature(x="spm"), log2.spm)



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
#' library(spm)
#' 
#' x = flrunif(10)
#' sin(x)
#' }
#' 
#' @name trig
#' @rdname trig
NULL



sin.spm = function(x)
{
  ptr = .Call(R_sin_spm, x@ptr)
  new("spm", ptr=ptr)
}

cos.spm = function(x)
{
  ptr = .Call(R_cos_spm, x@ptr)
  new("spm", ptr=ptr)
}

tan.spm = function(x)
{
  ptr = .Call(R_tan_spm, x@ptr)
  new("spm", ptr=ptr)
}

asin.spm = function(x)
{
  ptr = .Call(R_asin_spm, x@ptr)
  new("spm", ptr=ptr)
}

acos.spm = function(x)
{
  ptr = .Call(R_acos_spm, x@ptr)
  new("spm", ptr=ptr)
}

atan.spm = function(x)
{
  ptr = .Call(R_atan_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @rdname trig
#' @export
setMethod("sin", signature(x="spm"), sin.spm)

#' @rdname trig
#' @export
setMethod("cos", signature(x="spm"), cos.spm)

#' @rdname trig
#' @export
setMethod("tan", signature(x="spm"), tan.spm)

#' @rdname trig
#' @export
setMethod("asin", signature(x="spm"), asin.spm)

#' @rdname trig
#' @export
setMethod("acos", signature(x="spm"), acos.spm)

#' @rdname trig
#' @export
setMethod("atan", signature(x="spm"), atan.spm)



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
#' library(spm)
#' 
#' x = flrunif(10)
#' sinh(x)
#' }
#' 
#' @name hyperbolic
#' @rdname hyperbolic
NULL



sinh.spm = function(x)
{
  ptr = .Call(R_sinh_spm, x@ptr)
  new("spm", ptr=ptr)
}

cosh.spm = function(x)
{
  ptr = .Call(R_cosh_spm, x@ptr)
  new("spm", ptr=ptr)
}

tanh.spm = function(x)
{
  ptr = .Call(R_tanh_spm, x@ptr)
  new("spm", ptr=ptr)
}

asinh.spm = function(x)
{
  ptr = .Call(R_asinh_spm, x@ptr)
  new("spm", ptr=ptr)
}

acosh.spm = function(x)
{
  ptr = .Call(R_acosh_spm, x@ptr)
  new("spm", ptr=ptr)
}

atanh.spm = function(x)
{
  ptr = .Call(R_atanh_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @rdname hyperbolic
#' @export
setMethod("sinh", signature(x="spm"), sinh.spm)

#' @rdname hyperbolic
#' @export
setMethod("cosh", signature(x="spm"), cosh.spm)

#' @rdname hyperbolic
#' @export
setMethod("tanh", signature(x="spm"), tanh.spm)

#' @rdname hyperbolic
#' @export
setMethod("asinh", signature(x="spm"), asinh.spm)

#' @rdname hyperbolic
#' @export
setMethod("acosh", signature(x="spm"), acosh.spm)

#' @rdname hyperbolic
#' @export
setMethod("atanh", signature(x="spm"), atanh.spm)



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
#' library(spm)
#' 
#' x = flrunif(10)
#' sqrt(x)
#' }
#' 
#' @name miscmath
#' @rdname miscmath
NULL



abs.spm = function(x)
{
  ptr = .Call(R_abs_spm, x@ptr)
  new("spm", ptr=ptr)
}

sqrt.spm = function(x)
{
  ptr = .Call(R_sqrt_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @rdname miscmath
#' @export
setMethod("abs", signature(x="spm"), abs.spm)

#' @rdname miscmath
#' @export
setMethod("sqrt", signature(x="spm"), sqrt.spm)



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
#' library(spm)
#' 
#' x = flrunif(10)
#' lgamma(x)
#' }
#' 
#' @name specialmath
#' @rdname specialmath
NULL



gamma.spm = function(x)
{
  ptr = .Call(R_gamma_spm, x@ptr)
  new("spm", ptr=ptr)
}

lgamma.spm = function(x)
{
  ptr = .Call(R_lgamma_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @rdname specialmath
#' @export
setMethod("gamma", signature(x="spm"), gamma.spm)

#' @rdname specialmath
#' @export
setMethod("lgamma", signature(x="spm"), lgamma.spm)



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
#' An integre vector/matrix of the same dimensions as the input.
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' 
#' x = flrnorm(10)
#' is.nan(sqrt(x))
#' }
#' 
#' @name mathis
#' @rdname mathis
NULL



is.finite.spm = function(x)
{
  .Call(R_isfinite_spm, x@ptr)
}

is.infinite.spm = function(x)
{
  .Call(R_isinfinite_spm, x@ptr)
}

is.nan.spm = function(x)
{
  .Call(R_isnan_spm, x@ptr)
}



#' @rdname mathis
#' @export
setMethod("is.finite", signature(x="spm"), is.finite.spm)

#' @rdname mathis
#' @export
setMethod("is.infinite", signature(x="spm"), is.infinite.spm)

#' @rdname mathis
#' @export
setMethod("is.nan", signature(x="spm"), is.nan.spm)
