#' xpose
#' 
#' Transpose a float vector/matrix.
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
#' dim(s)
#' ts = t(s)
#' dim(ts)
#' 
#' @name xpose
#' @rdname xpose
NULL



xpose_float32 = function(x)
{
  ret = .Call(R_xpose_spm, DATA(x))
  float32(ret)
}



#' @rdname xpose
#' @export
setMethod("t", signature(x="float32"), xpose_float32)
