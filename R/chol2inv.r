#' chol2inv
#' 
#' Return the inverse of the original matrix using the Cholesky factorization of
#' a float vector/matrix.
#' 
#' @param x
#' A float vector/matrix.
#' @param size
#' The number of columns to use.
#' @param LINPACK
#' Ignored.
#' 
#' @return
#' A float vector/matrix.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' cp = crossprod(s)
#' cp %*% chol2inv(chol(cp))
#' 
#' @name chol2inv
#' @rdname chol2inv
NULL



chol2inv_float32 = function(x, size=NCOL(x), LINPACK=FALSE)
{
  ret = .Call(R_chol2inv_spm, DATA(x), as.integer(size))
  float32(ret)
}



#' @rdname chol2inv
#' @export
setMethod("chol2inv", signature(x="float32"), chol2inv_float32)
