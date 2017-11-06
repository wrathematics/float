chol2inv_float32 = function(x, size=NCOL(x), LINPACK=FALSE)
{
  ret = .Call(R_chol2inv_spm, DATA(x), size)
  new("float32", Data=ret)
}



#' @export
setMethod("chol2inv", signature(x="float32"), chol2inv_float32)
