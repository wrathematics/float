#' float32
#' 
#' A \code{float32} class constructor. For developers only.
#' 
#' @details
#' Wraps the integer-type data in the \code{float32} S4 class, so that the data
#' will be interpreted as 32-bit floats.
#' 
#' If instead you merely want to convert numeric/double data to float type,
#' instead you should call \code{fl(x)}.
#' 
#' @param x
#' Input data of type integer.
#' 
#' @return
#' A \code{float32} class object.
#' 
#' @export
float32 = function(x)
{
  if (!is.integer(x))
    stop("data must have integer storage; did you mean to call fl(x)?")
  
  new("float32", Data=x)
}
