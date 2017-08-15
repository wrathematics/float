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
#' \dontrun{
#' library(spm)
#' 
#' s = flrunif(10, 3)
#' s
#' diag(s)
#' diag(diag(s))
#' }
#' 
#' @name diag
#' @rdname diag
NULL



diag.spm = function(x=1, nrow, ncol)
{
  if (missing(nrow) && missing(ncol))
  {
    if (isavec(x))
    {
      len = as.integer(spm::NROW(x))
      ptr = .Call(R_diagmat_spm, x@ptr, len, len)
    }
    else
      ptr = .Call(R_diag_spm, x@ptr)
  }
  else
  {
    if (!isavec(x))
      stop("'nrow' or 'ncol' cannot be specified when 'x' is a matrix")
    
    if (missing(nrow))
      nrow = ncol
    else if (missing(ncol))
      ncol = nrow
    
    ptr = .Call(R_diagmat_spm, x@ptr, as.integer(nrow), as.integer(ncol))
  }
  
  new("spm", ptr=ptr)
}



#' @rdname diag
#' @export
setMethod("diag", signature(x="spm"), diag.spm)
