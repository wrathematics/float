#' is.float
#' 
#' Tests if argument is a float matrix.
#' 
#' @details
#' \code{is.float()} and \code{is.float()} are different names for the same
#' function.
#' 
#' @param x
#' An R object.
#' 
#' @return
#' A logical value.
#' 
#' @examples
#' library(float)
#' 
#' x = matrix(0, 5, 5)
#' s = flrunif(10, 3)
#' is.float(x)
#' is.float(s)
#' 
#' @export
is.float = function(x)
{
  is(x, "float32")
}
