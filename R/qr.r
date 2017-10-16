#' QR
#' 
#' QR factorization and related functions.
#' 
#' @details
#' The factorization is performed by the LAPACK routine \code{sgeqp3()}.
#' 
#' @param x
#' A float matrix.
#' @param tol
#' The tolerance for determining numerical column rank.
#' @param ...
#' Ignored.
#' @param qr
#' Output of \code{qr()}.
#' @param complete
#' TODO
#' @param Dvec
#' Ignored
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = flrunif(10, 3)
#' qr(x)
#' }
#' 
#' @name qr
#' @rdname qr
NULL



qr_float32 = function(x, tol=1e-7, ...) 
{
  ret = .Call(R_qr_spm, DATA(x), tol)
  ret$qr = new("spm", ptr=ret$qr)
  ret$qraux = new("spm", ptr=ret$qraux)
  
  ret
}

qrQ_float32 = function(qr, complete=FALSE, Dvec) 
{
  if (!is.qr(qr)) 
    stop("argument is not a QR decomposition")
  
  if (is.spm(qr$qr))
  {
    ret = .Call(R_qrQ_spm, qr$DATA(qr), qr$DATA(qraux))
    new("float32", Data=ret)
  }
  else
    base::qr.Q(qr, complete, Dvec)
}

qrR_float32 = function(qr, complete=FALSE) 
{
  if (!is.qr(qr)) 
    stop("argument is not a QR decomposition")
  
  if (is.spm(qr$qr))
  {
    ret = .Call(R_qrR_spm, qr$qr@ptr)
    new("float32", Data=ret)
  }
  else
    base::qr.R(qr, complete)
}



#' @rdname qr
#' @export
setMethod("qr", signature(x="float32"), qr_float32)

#' @rdname qr
#' @export
setMethod("qr.Q", signature(qr="ANY"), qrQ_float32)

#' @rdname qr
#' @export
setMethod("qr.R", signature(qr="ANY"), qrR_float32)
