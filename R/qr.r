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



qr.spm = function(x, tol=1e-7, ...) 
{
  ret = .Call(R_qr_spm, x@ptr, tol)
  ret$qr = new("spm", ptr=ret$qr)
  ret$qraux = new("spm", ptr=ret$qraux)
  
  ret
}

qrQ.spm = function(qr, complete=FALSE, Dvec) 
{
  if (!is.qr(qr)) 
    stop("argument is not a QR decomposition")
  
  if (is.spm(qr$qr))
  {
    ptr = .Call(R_qrQ_spm, qr$qr@ptr, qr$qraux@ptr)
    new("spm", ptr=ptr)
  }
  else
    base::qr.Q(qr, complete, Dvec)
}

qrR.spm = function(qr, complete=FALSE) 
{
  if (!is.qr(qr)) 
    stop("argument is not a QR decomposition")
  
  if (is.spm(qr$qr))
  {
    ptr = .Call(R_qrR_spm, qr$qr@ptr)
    new("spm", ptr=ptr)
  }
  else
    base::qr.R(qr, complete)
}



#' @rdname qr
#' @export
setMethod("qr", signature(x="spm"), qr.spm)

#' @rdname qr
#' @export
setMethod("qr.Q", signature(qr="ANY"), qrQ.spm)

#' @rdname qr
#' @export
setMethod("qr.R", signature(qr="ANY"), qrR.spm)
