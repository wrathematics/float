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



cp_float32 = function(x, y=NULL)
{
  if (is.spm(x))
  {
    if (is.null(y))
      d = .Call(R_crossprod_spm, DATA(x))
    else if (is.spm(y))
      d = .Call(R_crossprod_spmspm, DATA(x), DATA(y))
    else
      return(base::crossprod(dbl(x), y))
  }
  else if (is.matrix(x) && is.spm(y))
    return(base::crossprod(x, dbl(y)))
  else
    return(base::crossprod(x, y))
  
  new("float32", Data=d)
}

tcp_float32 = function(x, y=NULL)
{
  if (is.spm(x))
  {
    if (is.null(y))
      d = .Call(R_tcrossprod_spm, DATA(x))
    else if (is.spm(y))
      d = .Call(R_tcrossprod_spmspm, DATA(x), DATA(y))
    else
      return(base::tcrossprod(dbl(x), y))
  }
  else if (is.matrix(x) && is.spm(y))
    return(base::tcrossprod(x, dbl(y)))
  else
    return(base::tcrossprod(x, y))
  
  new("float32", Data=d)
}



#' @rdname crossprod
#' @export
setMethod("crossprod", signature(x="Mat", y="ANY"), cp_float32)

#' @rdname crossprod
#' @export
setMethod("tcrossprod", signature(x="Mat", y="ANY"), tcp_float32)
