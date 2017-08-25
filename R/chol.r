#' chol
#' 
#' Extract subsets of a float vector/matrix.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' A float vector/matrix.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' s = flrunif(10, 3)
#' cp = crossprod(s)
#' chol(cp)
#' }
#' 
#' @name chol
#' @rdname chol
NULL



chol.spm = function(x)
{
  ptr = .Call(R_chol_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @rdname chol
#' @export
setMethod("chol", signature(x="spm"), chol.spm)
