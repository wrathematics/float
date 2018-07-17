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



#' float
#' 
#' An analogue to \code{integer()} and \code{double()} for preallocation.
#' 
#' @details
#' If both of \code{nrow} and \code{ncol} are specified, then \code{length} is
#' ignored, and the retor is a matrix. If one (but not the other) of \code{nrow}
#' or \code{ncol} is given, then the function errors. Otherwise, a vector of
#' length \code{length} is returned.
#' 
#' @param length
#' Input data of type integer.
#' @param nrow,ncol
#' Number of rows/columns if a matrix return is desired. See details section for
#' more information.
#' 
#' @return
#' A float vector/matrix of 0's.
#' 
#' @examples
#' library(float)
#' 
#' float(10)
#' float(nrow=2, ncol=3)
#' 
#' @export
float = function(length=0, nrow, ncol)
{
  if (!missing(nrow) && !missing(ncol))
    isamat = TRUE
  else if (!missing(nrow) || !missing(ncol))
    stop("either both or neither 'nrow' and 'ncol' must be specified")
  else
    isamat = FALSE
  
  if (isamat)
    length = nrow*ncol
  
  x = integer(length)
  
  if (isamat)
    dim(x) = c(nrow, ncol)
    
  float32(x)
}
