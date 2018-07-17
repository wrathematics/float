#' rep
#' 
#' Replicate elements of a float vector/matrix.
#' 
#' @param x
#' A float matrix.
#' @param ...
#' Additional arguments (passed to \code{base::rep}).
#'  
#' @return 
#' A float vector.
#' 
#' @examples
#' library(float)
#' x = fl(matrix(1:6, 3, 2))
#' 
#' rep(x, 5)
#' 
#' @name rep
#' @rdname rep
NULL



#' @rdname rep
#' @export
rep.float32 = function(x, ...)
{
  x_rep = rep(DATA(x), ...)
  float32(x_rep)
}
