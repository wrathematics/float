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
