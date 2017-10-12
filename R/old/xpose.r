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
#' \dontrun{
#' library(float)
#' 
#' s = flrunif(10, 3)
#' dim(s)
#' ts = t(s)
#' dim(ts)
#' }
#' 
#' @name xpose
#' @rdname xpose
NULL



xpose.spm = function(x)
{
  ptr = .Call(R_xpose_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @rdname xpose
#' @export
setMethod("t", signature(x="spm"), xpose.spm)
