#' backsolve
#' 
#' Solve a triangular system.
#' 
#' @param r,l
#' A triangular coefficients matrix.
#' @param x
#' The right hand sides.
#' @param k
#' The number of equations (columns of r + rows of x) to use.
#' @param upper.tri
#' Should the upper triangle be used? (if not the lower is)
#' @param transpose
#' Should the transposed coefficients matrix be used? More efficient than
#' manually transposing with \code{t()}.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' cp = crossprod(s)
#' y = fl(1:3)
#' backsolve(cp, y)
#' 
#' @name backsolve
#' @rdname backsolve
NULL



backsolve_float32 = function(r, x, k=ncol(r), upper.tri=TRUE, transpose=FALSE)
{
  if (is.integer(r))
  {
    if (is.float(x))
      r = fl(r)
  }
  
  if (is.integer(x))
  {
    if (is.float(r))
      x = fl(x)
  }
  
  if (is.double(r) || is.double(x))
  {
    if (is.float(r))
      r = dbl(r)
    if (is.float(x))
      x = dbl(x)
    
    backsolve(r, x, k, upper.tri, transpose)
  }
  else
  {
    if (!is.numeric(k) || k < 1 || k > nrow(r) || is.na(k))
      stop("invalid 'k' argument")
    
    ret = .Call(R_backsolve_spm, DATA(r), DATA(x), as.integer(upper.tri), as.integer(transpose), as.integer(k))
    float32(ret)
  }
}

forwardsolve_float32 = function(l, x, k=ncol(l), upper.tri=FALSE, transpose=FALSE)
{
  backsolve_float32(l, x, k, upper.tri, transpose)
}



#' @rdname backsolve
#' @export
setMethod("backsolve", signature(r="float32", x="float32"), backsolve_float32)

#' @rdname backsolve
#' @export
setMethod("backsolve", signature(r="float32", x="BaseLinAlg"), backsolve_float32)

#' @rdname backsolve
#' @export
setMethod("backsolve", signature(r="BaseLinAlg", x="float32"), backsolve_float32)



#' @rdname backsolve
#' @export
setMethod("forwardsolve", signature(l="float32", x="float32"), forwardsolve_float32)

#' @rdname backsolve
#' @export
setMethod("forwardsolve", signature(l="float32", x="BaseLinAlg"), forwardsolve_float32)

#' @rdname backsolve
#' @export
setMethod("forwardsolve", signature(l="BaseLinAlg", x="float32"), forwardsolve_float32)
