#' @export
mat2spm = function(x)
{
  if (!is.numeric(x))
    stop("input 'x' must be a numeric vector/matrix")
  
  ptr = .Call(R_mat2spm, x)
  new("spm", ptr=ptr)
}



#' @export
spm2mat = function(x)
{
  if (!is.spm(x))
    stop("input 'x' must be a spm (single precision matrix)")
  
  .Call(R_spm2mat, x@ptr)
}
