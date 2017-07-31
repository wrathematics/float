#' is.spm
#' 
#' Tests if argument is a float matrix.
#' 
#' @param x
#' An R object.
#' 
#' @return
#' A logical value.
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' 
#' x = matrix(0, 5, 5)
#' s = flrunif(10, 3)
#' is.spm(x)
#' is.spm(s)
#' }
#' 
#' @export
is.spm = function(x)
{
  is(x, "spm")
}
