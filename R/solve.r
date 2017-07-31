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
#' \dontrun{
#' library(spm)
#' 
#' s = flrunif(10, 3)
#' cp = crossprod(s)
#' solve(cp)
#' 
#' y = fl(1:3)
#' solve(cp, y)
#' }
#' 
#' @name solve
#' @rdname solve
NULL



solve.spm = function(a, b, ...)
{
  if (missing(b))
    ptr = .Call(R_solve_spm, a@ptr)
  else
  {
    if (is.integer(b))
      b = mat2spm(b)
    
    if (is.spm(b))
      ptr = .Call(R_solve_spmspm, a@ptr, b@ptr)
    else if (is.numeric(b))
      return(solve(spm2mat(a), b))
  }
  
  new("spm", ptr=ptr)
}



#' @rdname solve
#' @export
setMethod("solve", signature(a="spm", b="ANY"), solve.spm)
