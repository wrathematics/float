#' chol
#' 
#' Cholesky factorization for a float vector/matrix.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' A float vector/matrix.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' cp = crossprod(s)
#' chol(cp)
#' 
#' @useDynLib float R_chol_spm
#' @name chol
#' @rdname chol
NULL



chol_float32 = function(x)
{
  ret = .Call(R_chol_spm, DATA(x))
  float32(ret)
}



#' @rdname chol
#' @export
setMethod("chol", signature(x="float32"), chol_float32)
