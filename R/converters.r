#' @export
mat2spm = function(x)
{
  if (!is.numeric(x))
    stop("input 'x' must be a numeric vector/matrix")
  
  ptr = .Call(R_mat2spm, x)
  new("spm", ptr=ptr)
}

#' @export
fl = mat2spm



#' @export
spm2mat = function(x)
{
  if (!is.spm(x))
    stop("input 'x' must be a spv/spm (single precision vector/matrix)")
  
  .Call(R_spm2mat, x@ptr)
}

#' @export
dbl = spm2mat
