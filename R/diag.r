diag.spm = function(x, nrow, ncol)
{
  .Call(R_diag_spm, x@ptr)
}



#' @export
setMethod("diag", signature(x="spm"), diag.spm)
