isSymmetric.spm = function(object, ...)
{
  .Call(R_isSymmetric_spm, object@ptr)
}



#' @export
setMethod("isSymmetric", signature(object="spm"), isSymmetric.spm)
