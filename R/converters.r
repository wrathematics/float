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
#' 
#' @return
#' The data stored in the type of whatever was asked for (the opposite of the
#' input).
#' 
#' @examples
#' \dontrun{
#' library(spm)
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
mat2spm = function(x)
{
  if (!is.numeric(x))
    stop("input 'x' must be a numeric vector/matrix")
  
  ptr = .Call(R_mat2spm, x)
  new("spm", ptr=ptr)
}

#' @rdname converters
#' @export
fl = mat2spm



#' @rdname converters
#' @export
spm2mat = function(x)
{
  if (!is.spm(x))
    stop("input 'x' must be a spv/spm (single precision vector/matrix)")
  
  .Call(R_spm2mat, x@ptr)
}

#' @rdname converters
#' @export
dbl = spm2mat
