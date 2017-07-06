xpose.spm = function(x)
{
  ptr = .Call(R_xpose_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @export
setMethod("t", signature(x="spm"), xpose.spm)
