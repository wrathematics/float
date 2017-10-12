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
#' \dontrun{
#' library(float)
#' 
#' s = flrunif(10, 3)
#' norm(s)
#' }
#' 
#' @name norm
#' @rdname norm
NULL



norm.spm = function(x, type=c("O", "I", "F", "M", "2"))
{
  type = toupper(type)
  
  if (type == "2")
    La.svd(x, nu=0, nv=0)$d[1L]
  else
  {
    ptr = .Call(R_norm_spm, x@ptr, type)
    new("spm", ptr=ptr)
  }
}



#' @rdname norm
#' @export
setMethod("norm", signature(x="spm"), norm.spm)
