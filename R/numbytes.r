numbytes.spm = function(x)
{
  ret = .Call(R_numbytes_spm, x@ptr)
  class(ret) = "object_size"
  ret
}

#' @export
setMethod("object.size", signature(x="spm"), numbytes.spm)
