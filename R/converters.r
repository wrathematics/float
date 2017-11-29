#' converters
#' 
#' Convert between a numeric vector/matrix and a float vector/matrix.
#' 
#' @param x
#' A numeric or float vector/matrix.
#' @param strict
#' Should the function error if given the wrong kind of input? Otherwise it just
#' silently returns the input.
#' @param mode,...
#' Ignored.
#' 
#' @return
#' The data stored in the type of whatever was asked for (the opposite of the
#' input).
#' 
#' @examples
#' library(float)
#' 
#' x = matrix(1:30, 10, 3)
#' s = fl(x)
#' 
#' y = dbl(s)
#' 
#' all.equal(x, y)
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
    if (is.float(x) && !isTRUE(strict))
      return(x)
    else
      stop("input 'x' must be a numeric or logical vector/matrix")
  }
  
  d = .Call(R_mat2spm, x)
  float32(d)
}

#' @rdname converters
#' @export
dbl = function(x, strict=FALSE)
{
  if (!is.float(x))
  {
    if (isTRUE(strict))
      stop("input 'x' must be float32")
    else
    {
      if (!is.double(x))
        storage.mode(x) = "double"
      
      return(x)
    }
  }
  
  .Call(R_spm2mat, DATA(x))
}

#' @rdname converters
#' @export
int = function(x, strict=FALSE)
{
  if (!is.float(x))
  {
    if (isTRUE(strict))
      stop("input 'x' must be float32")
    else
    {
      if (!is.integer(x))
        storage.mode(x) = "integer"
      
      return(x)
    }
  }
  
  .Call(R_spm2int, DATA(x))
}



#' @method as.vector float32
#' @rdname converters
#' @export
as.vector.float32 = function(x, mode="any")
{
  if (!isavec(x))
    dim(x@Data) = NULL
  
  x
}

#' @method as.matrix float32
#' @rdname converters
#' @export
as.matrix.float32 = function(x, ...)
{
  if (isavec(x))
    dim(x@Data) = c(length(DATA(x)), 1L)
  
  x
}



#' @rdname converters
#' @export
setMethod("typeof", signature(x="float32"), function(x) "float32")

#' @rdname converters
#' @export
setMethod("storage.mode", signature(x="float32"), function(x) "float32")
