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
#' library(spm)
#' 
#' s = flrunif(10, 3)
#' s[, -1]
#' s[c(1, 3, 5, 7), 1:2]
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
