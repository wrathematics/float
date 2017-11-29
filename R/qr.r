#' QR
#' 
#' QR factorization and related functions.
#' 
#' @details
#' The factorization is performed by the LAPACK routine \code{sgeqp3()}. This
#' should be similar to calling \code{qr()} on an ordinary R matrix with the
#' argument \code{LAPACK=TRUE}. Calling \code{qr(x, LAPACK=FALSE)} on a double
#' precision matrix 'x' (the default) will not be comparable in performance (it
#' is much slower) or numerics to calling \code{qr(s)} where 's' is single a
#' float matrix.
#' 
#' @param x
#' A float matrix.
#' @param y
#' A vector/matrix or right hand sides (int, float, or double).
#' @param tol
#' The tolerance for determining numerical column rank.
#' @param ...
#' Ignored.
#' @param qr
#' Output of \code{qr()}.
#' @param complete
#' Should the complete or truncated factor be returned?
#' @param Dvec
#' Vector of diagonals to use when re-constructing Q (default is 1's).
#' 
#' @examples
#' library(float)
#' 
#' x = flrunif(10, 3)
#' qr(x)
#' 
#' @name qr
#' @rdname qr
NULL



qr_float32 = function(x, tol=1e-7, ...) 
{
  ret = .Call(R_qr_spm, DATA(x), tol)
  ret$qr = float32(ret$qr)
  ret$qraux = float32(ret$qraux)
  
  ret
}

qrQ_float32 = function(qr, complete=FALSE, Dvec) 
{
  if (!is.qr(qr)) 
    stop("argument is not a QR decomposition")
  
  m = NROW(qr$qr)
  n = NCOL(qr$qr)
  
  if (is.float(qr$qr))
  {
    # ret = .Call(R_qrQ_spm, qr$DATA(qr), qr$DATA(qraux))
    if (missing(Dvec))
    {
      ret = .Call(R_qrQ_spm, DATA(qr$qr), DATA(qr$qraux), complete)
      float32(ret)
    }
    else
    {
      if (is.integer(Dvec))
      {
        Dvec = fl(Dvec)
        if (complete)
          RHS = diag(Dvec, m, m)
        else
          RHS = diag(Dvec[1:m], m, min(m, n))
      }
      else if (is.double(Dvec))
      {
        qr$qr = dbl(qr$qr)
        return(base::qr.Q(qr, complete, Dvec))
      }
      
      qrqy_float32(qr, RHS)
    }
  }
  else
  {
    if (!missing(Dvec) && is.float(Dvec))
      Dvec = dbl(Dvec)
    
    base::qr.Q(qr, complete, Dvec)
  }
}

qrR_float32 = function(qr, complete=FALSE) 
{
  if (!is.qr(qr)) 
    stop("argument is not a QR decomposition")
  
  if (is.float(qr$qr))
  {
    ret = .Call(R_qrR_spm, DATA(qr$qr), as.logical(complete))
    float32(ret)
  }
  else
    base::qr.R(qr, complete)
}

qrqy = function(qr, y, trans)
{
  if (!is.qr(qr)) 
    stop("argument is not a QR decomposition")
  
  if (NROW(y) != NROW(qr$qr))
    stop("'qr' and 'y' must have the same number of rows")
  
  if (is.float(qr$qr))
  {
    if (is.integer(y))
      y = fl(y)
    else if (is.double(y))
    {
      qr$qr = dbl(qr$qr)
      qr$qraux = dbl(qr$qraux)
      return(base::qr.qy(qr, y))
    }
    else if (!is.float(y))
      stop("argument 'y' must be atomic")
    
    ret = .Call(R_qrqy_spm, DATA(qr$qr), DATA(qr$qraux), DATA(y), trans)
    float32(ret)
  }
  else
  {
    if (is.float(y))
      y = dbl(y)
    
    base::qr.qy(qr, y)
  }
}

qrqy_float32 = function(qr, y)
{
  qrqy(qr, y, FALSE)
}

qrtqy_float32 = function(qr, y)
{
  qrqy(qr, y, TRUE)
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

#' @rdname qr
#' @export
setMethod("qr.qy", signature(qr="ANY"), qrqy_float32)

#' @rdname qr
#' @export
setMethod("qr.qty", signature(qr="ANY"), qrtqy_float32)
