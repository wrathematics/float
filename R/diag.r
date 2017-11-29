#' diag
#' 
#' Methods for getting the diagonal of a float matrix, or constructing a float
#' matrix given a float vector.
#' 
#' @param x
#' A float vector (create a diagonal matrix) or matrix (get its diagonal).
#' @param nrow,ncol
#' As in base R's \code{diag()}.
#' 
#' @return
#' A float vector or matrix, depending on the input.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' s
#' diag(s)
#' diag(diag(s))
#' 
#' @name diag
#' @rdname diag
NULL



#' @rdname diag
#' @export
setMethod("diag", signature(x="float32"),
  function(x = 1, nrow, ncol)
  {
    if (missing(nrow) && missing(ncol))
      Data = diag(DATA(x))
    else
      Data = diag(DATA(x), nrow, ncol)
    
    if (is.double(Data))
      storage.mode(Data) = "integer"
    
    x@Data = Data
    x
  }
)
