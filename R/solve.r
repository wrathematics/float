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



#' @export
setMethod("solve", signature(a="spm", b="ANY"), solve.spm)
