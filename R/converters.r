#' converters
#' 
#' Convert between a numeric vector/matrix and a float vector/matrix.
#' 
#' @details
#' \code{fl()} is shorthand for \code{mat2spm()}; it behaves like a caster
#' (i.e., TO float). \code{dbl()} is shorthand for \code{spm2mat()}, casting
#' TO double (numeric matrix).
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
#' s = fl(x) ### same as mat2spm(x)
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
mat2spm = function(x, strict=FALSE)
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
fl = mat2spm



#' @rdname converters
#' @export
spm2mat = function(x, strict=FALSE)
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

#' @rdname converters
#' @export
dbl = spm2mat
