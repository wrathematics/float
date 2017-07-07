diag.spm = function(x, nrow, ncol)
{
  ptr = .Call(R_diag_spm, x@ptr)
  new("spm", ptr=ptr)
}



#' @export
setMethod("diag", signature(x="spm"), diag.spm)
