#' converters
#' 
#' Convert between a numeric vector/matrix and a float vector/matrix.
#' 
#' @param x
#' A numeric or float vector/matrix.
#' @param strict
#' Should the function error if given the wrong kind of input? Otherwise it just
#' silently returns the input.
#' 
#' @return
#' The data stored in the type of whatever was asked for (the opposite of the
#' input).
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = matrix(1:30, 10, 3)
#' s = fl(x)
#' 
#' y = dbl(s)
#' 
#' all.equal(x, y)
#' }
#' 
#' @name converters
#' @rdname converters
NULL



#' @rdname converters
#' @export
fl = function(x, strict=FALSE)
{
  if (!is.numeric(x) && !is.logical(x))
  {
    if (is.spm(x) && !isTRUE(strict))
      return(x)
    else
      stop("input 'x' must be a numeric or logical vector/matrix")
  }
  
  ptr = .Call(R_mat2spm, x)
  new("spm", ptr=ptr)
}



#' @rdname converters
#' @export
dbl = function(x, strict=FALSE)
{
  if (!is.spm(x))
  {
    if (isTRUE(strict))
      stop("input 'x' must be a spv/spm (single precision vector/matrix)")
    else
      return(x)
  }
  
  .Call(R_spm2mat, x@ptr)
}
