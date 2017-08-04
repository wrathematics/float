#' SVD
#' 
#' SVD factorization.
#' 
#' @details
#' The factorization is performed by the LAPACK routine \code{sgesdd()}.
#' 
#' @param x
#' A float matrix.
#' @param nu,nv
#' The number of left/right singular vectors to return.
#' @param LINPACK
#' Ignored
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' 
#' x = flrunif(10, 3)
#' svd(x)
#' }
#' 
#' @name svd
#' @rdname svd
NULL



La.svd.spm = function(x, nu=min(n, p), nv=min(n, p)) 
{
  n = nrow(x)
  p = ncol(x)
  
  if (n == 0 || p == 0)
    stop("a dimension is zero")
  
  nu = as.integer(nu)
  if (is.na(nu) || nu < 0)
    stop("argument must be coercible to non-negative integer")
  
  nv = as.integer(nv)
  if (is.na(nv) || nv < 0)
    stop("argument must be coercible to non-negative integer")
  
  ret = .Call(R_svd_spm, x@ptr, min(n, nu), min(p, nv))
  
  ret$d = new("spm", ptr=ret$d)
  if (nu)
    ret$u = new("spm", ptr=ret$u)
  if (nv)
    ret$vt = new("spm", ptr=ret$vt)
  
  ret
}



svd.spm = function(x, nu=min(n, p), nv=min(n, p), LINPACK=FALSE) 
{
  n = nrow(x)
  p = ncol(x)
  
  ret = La.svd(x, nu, nv)
  if (nv)
  {
    ret$v = t(ret$vt)
    ret$vt = NULL
  }
  
  ret
}



#' @rdname svd
#' @export
setMethod("La.svd", signature(x="spm"), La.svd.spm)

#' @rdname svd
#' @export
setMethod("svd", signature(x="spm"), svd.spm)
