#' crossprod
#' 
#' Croddproducts.
#' 
#' @details
#' If \code{y} is a numeric matrix, then \code{x} will be promoted to a numeric
#' matrix, and the return will therefore be numeric (not float).
#' 
#' @param x
#' A float vector/matrix.
#' @param y
#' Either \code{NULL}, or a numeric/float matrix.
#' 
#' @return
#' A float matrix (unless \code{y} is numeric; see details section).
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' s = flrunif(10, 3)
#' crossprod(s)
#' tcrossprod(s)
#' }
#' 
#' @name crossprod
#' @rdname crossprod
NULL



cp.spm = function(x, y=NULL)
{
  if (is.spm(x))
  {
    if (is.null(y))
      ptr = .Call(R_crossprod_spm, x@ptr)
    else if (is.spm(y))
      ptr = .Call(R_crossprod_spmspm, x@ptr, y@ptr)
    else
      return(base::crossprod(dbl(x), y))
  }
  else if (is.matrix(x) && is.spm(y))
    return(base::crossprod(x, dbl(y)))
  else
    return(base::crossprod(x, y))
  
  new("spm", ptr=ptr)
}

tcp.spm = function(x, y=NULL)
{
  if (is.spm(x))
  {
    if (is.null(y))
      ptr = .Call(R_tcrossprod_spm, x@ptr)
    else if (is.spm(y))
      ptr = .Call(R_tcrossprod_spmspm, x@ptr, y@ptr)
    else
      return(base::tcrossprod(dbl(x), y))
  }
  else if (is.matrix(x) && is.spm(y))
    return(base::tcrossprod(x, dbl(y)))
  else
    return(base::tcrossprod(x, y))
  
  new("spm", ptr=ptr)
}



#' @rdname crossprod
#' @export
setMethod("crossprod", signature(x="Mat", y="ANY"), cp.spm)

#' @rdname crossprod
#' @export
setMethod("tcrossprod", signature(x="Mat", y="ANY"), tcp.spm)
