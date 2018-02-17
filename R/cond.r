#' rcond
#' 
#' Compute matrix norm.
#' 
#' @param x
#' A float vector/matrix.
#' @param norm
#' "O"-ne or "I"-nfinity norm.
#' @param triangular
#' Should only the lower triangle be used?
#' @param ...
#' Additional arguments.
#' 
#' @return
#' A single float.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' rcond(s)
#' 
#' @name rcond
#' @rdname rcond
NULL



rcond_float32 = function(x, norm=c("O","I","1"), triangular=FALSE, ...)
{
  if (isavec(x))
    stop("is.matrix(x) is not TRUE")
  
  if (missing(norm))
    norm = "O"
  
  m = nrow(x)
  n = ncol(x)
  
  if (m > n)
    rcond_float32(qr.R(qr(x)), norm=norm, ...)
  else if (m < n)
    rcond_float32(qr.R(qr(t(x))), norm=norm, ...)
  else
  {
    ret = .Call(R_rcond_spm, DATA(x), norm, triangular)
    float32(ret)
  }
}



#' @rdname rcond
#' @export
setMethod("rcond", signature(x="float32", norm="ANY"), rcond_float32)



### TODO kappa
