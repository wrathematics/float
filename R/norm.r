#' norm
#' 
#' Compute matrix norm.
#' 
#' @param x
#' A float vector/matrix.
#' @param type
#' "O"-ne, "I"-nfinity, "F"-robenius, "M"-ax modulus, and "2" norms.
#' 
#' @return
#' A single float.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' norm(s, type="O")
#' 
#' @name norm
#' @rdname norm
NULL



norm_float32 = function(x, type=c("O", "I", "F", "M", "2"))
{
  type = toupper(match.arg(type))
  
  if (type == "2")
    La.svd_float32(x, nu=0, nv=0)$d[1L]
  else
  {
    ret = .Call(R_norm_spm, DATA(x), type)
    float32(ret)
  }
}



#' @rdname norm
#' @export
setMethod("norm", signature(x="float32", type="ANY"), norm_float32)
