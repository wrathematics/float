#' isSymmetric
#' 
#' Test if a float matrix is symmetric.
#' 
#' @param object
#' A float vector/matrix.
#' @param ...
#' Ignored.
#' 
#' @return
#' A logical value.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' isSymmetric(s)
#' 
#' cp = crossprod(s)
#' isSymmetric(s)
#' 
#' @name isSymmetric
#' @rdname isSymmetric
NULL



isSymmetric_float32 = function(object, ...)
{
  .Call(R_isSymmetric_spm, DATA(object))
}



#' @rdname isSymmetric
#' @export
setMethod("isSymmetric", signature(object="float32"), isSymmetric_float32)
