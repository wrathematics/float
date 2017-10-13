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
#' @name backsolve
#' @rdname backsolve
NULL



backsolve_float32 = function(r, x, k=ncol(r), upper.tri=TRUE, transpose=FALSE)
{
  if (is.integer(r))
  {
    if (is.spm(x))
      r = fl(r)
  }
  
  if (is.integer(x))
  {
    if (is.spm(r))
      x = fl(x)
  }
  
  if (is.double(r) || is.double(x))
  {
    if (is.spm(r))
      r = dbl(r)
    if (is.spm(x))
      x = dbl(x)
    
    backsolve(r, x, k, upper.tri, transpose)
  }
  else
  {
    if (!is.numeric(k) || k < 1 || k > nrow(r) || is.na(k))
      stop("invalid 'k' argument")
    
    ret = .Call(R_backsolve_spm, DATA(r), DATA(x), as.integer(upper.tri), as.integer(transpose), as.integer(k))
    new("float32", Data=ret)
  }
}

forwardsolve_float32 = function(l, x, k=ncol(l), upper.tri=FALSE, transpose=FALSE)
{
  backsolve.spm(l, x, k, upper.tri, transpose)
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
