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
#' library(float)
#' 
#' x = flrunif(10, 3)
#' svd(x)
#' 
#' @useDynLib float R_svd_spm
#' @name svd
#' @rdname svd
NULL



utils::globalVariables(c("n", "p"))



La.svd_float32 = function(x, nu=min(n, p), nv=min(n, p)) 
{
  n = NROW(x)
  p = NCOL(x)
  
  if (n == 0 || p == 0)
    stop("a dimension is zero")
  
  nu = as.integer(nu)
  if (is.na(nu) || nu < 0)
    stop("argument must be coercible to non-negative integer")
  
  nv = as.integer(nv)
  if (is.na(nv) || nv < 0)
    stop("argument must be coercible to non-negative integer")
  
  ret = .Call(R_svd_spm, DATA(x), min(n, nu), min(p, nv))
  
  ret$d = float32(ret$d)
  if (nu)
    ret$u = float32(ret$u)
  if (nv)
    ret$vt = float32(ret$vt)
  
  ret
}



svd_float32 = function(x, nu=min(n, p), nv=min(n, p), LINPACK=FALSE) 
{
  n = NROW(x)
  p = NCOL(x)
  
  ret = La.svd_float32(x, nu, nv)
  if (nv)
  {
    ret$v = t(ret$vt)
    ret$vt = NULL
  }
  
  ret
}



#' @rdname svd
#' @export
setMethod("La.svd", signature(x="float32"), La.svd_float32)

#' @rdname svd
#' @export
setMethod("svd", signature(x="float32"), svd_float32)
