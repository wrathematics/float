#' solve
#' 
#' Solve a system of equations or invert a float matrix.
#' 
#' @param a,b
#' A float vector/matrix.
#' @param ...
#' Ignored.
#' 
#' @return
#' A float matrix if inverting.  If solving a system, a float vector if given
#' one "right hand side", and a float matrix otherwise (just like R). 
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' cp = crossprod(s)
#' solve(cp)
#' 
#' y = fl(1:3)
#' solve(cp, y)
#' 
#' @useDynLib float R_solve_spm R_solve_spmspm
#' @name solve
#' @rdname solve
NULL



solve_float32 = function(a, b, ...)
{
  if (missing(b))
    ret = .Call(R_solve_spm, DATA(a))
  else
  {
    if (is.integer(b))
      b = fl(b)
    
    if (is.float(b))
      ret = .Call(R_solve_spmspm, DATA(a), DATA(b))
    else if (is.numeric(b))
      return(solve(dbl(a), b))
  }
  
  float32(ret)
}



#' @rdname solve
#' @export
setMethod("solve", signature(a="float32", b="ANY"), solve_float32)
