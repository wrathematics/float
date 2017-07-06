chol.spm = function(x)
{
  ptr = .Call(R_chol_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @export
setMethod("chol", signature(x="spm"), chol.spm)
