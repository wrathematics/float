#' is.spm
#' 
#' Tests if argument is a float matrix.
#' 
#' @details
#' \code{is.spm()} and \code{is.float()} are different names for the same
#' function.
#' 
#' @param x
#' An R object.
#' 
#' @return
#' A logical value.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' x = matrix(0, 5, 5)
#' s = flrunif(10, 3)
#' is.spm(x)
#' is.spm(s)
#' }
#' 
#' @name is.spm
#' @rdname is.spm
NULL


#' @rdname is.spm
#' @export
is.spm = function(x)
{
  is(x, "spm")
}

#' @rdname is.spm
#' @export
is.float = is.spm
