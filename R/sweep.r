#' sweep
#' 
#' Extract subsets of a float vector/matrix.
#' 
#' @details
#' Note that if the length of \code{STATS} does not recycle exactly across
#' \code{MARGIN}, the results here will differ slightly from the results of
#' base R.
#' 
#' @param x
#' A float vector/matrix.
#' @param MARGIN
#' 1 (rows) or 2 (columns)
#' @param STATS
#' Vector to sweep out. 
#' @param FUN
#' Sweeping function; must be one of \code{"+"}, \code{"-"}, \code{"*"},  or
#' \code{"/"}. 
#' @param check.margin
#' Should x/STATS margin lengths be checked?
#' 
#' @return
#' A matrix of the same type as the highest precision input.
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' 
#' s = flrunif(10, 3)
#' sweep(s, 2, fl(1))
#' }
#' 
#' @name sweep
#' @rdname sweep
NULL



sweep.spm = function(x, MARGIN, STATS, FUN="-", check.margin=TRUE, ...) 
{
  if (is.double(STATS))
    return(sweep(dbl(x), MARGIN, STATS, FUN, check.margin, ...))
  else if (!is.logical(STATS) && !is.integer(STATS) && !is.spm(STATS))
    stop("non-numeric argument to binary operator")
  
  if (!isTRUE(all.equal(MARGIN, 1)) && !isTRUE(all.equal(MARGIN, 2)))
    stop("missing value where TRUE/FALSE needed")
  
  if (!is.character(FUN))
    stop("only '+', '-', '*', and '/' are implemented for floats")
  
  FUN = match.arg(FUN, c('+', '-', '*', '/'))
  
  if (isTRUE(check.margin))
  {
    if ((MARGIN == 1 && nrow(x)%%length(STATS)) || (MARGIN == 2 && ncol(x)%%length(STATS)))
      warning("STATS does not recycle exactly across MARGIN")
  }
  
  ptr = .Call(R_sweep_spm, x@ptr, as.integer(MARGIN), STATS, FUN)
  new("spm", ptr=ptr)
}



#' @rdname sweep
#' @export
setMethod("sweep", signature(x="spm"), sweep.spm)
