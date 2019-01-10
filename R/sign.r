#' sign
#' 
#' Sign.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @return
#' A float vector/matrix.
#' 
#' @useDynLib float R_sign_spm
#' @name sign
#' @rdname sign
NULL



sign_float32 = function(x)
{
  .Call(R_sign_spm, DATA(x))
}



#' @rdname sign
#' @export
setMethod("sign", signature(x="float32"), sign_float32)
