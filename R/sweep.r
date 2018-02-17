#' sweep
#' 
#' Sweep a vector through a float matrix.
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
#' @param ...
#' Theoretically these are additional arguments passed to an arbitrary function.
#' However, we only support basic arithmetic, so they are ignored.
#' 
#' @return
#' A matrix of the same type as the highest precision input.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' sweep(s, 2, fl(1))
#' 
#' @name sweep
#' @rdname sweep
NULL



sweep_float32 = function(x, MARGIN, STATS, FUN="-", check.margin=TRUE, ...) 
{
  if (is.double(STATS))
    return(sweep(dbl(x), MARGIN, STATS, FUN, check.margin, ...))
  else if (!is.logical(STATS) && !is.integer(STATS) && !is.float(STATS))
    stop("non-numeric argument to binary operator")
  
  if (isavec(x))
    stop("Error in array(STATS, dims[perm]) : 'dims' cannot be of length 0", call.=FALSE)
  
  if (!isTRUE(all.equal(MARGIN, 1)) && !isTRUE(all.equal(MARGIN, 2)))
    stop("missing value where TRUE/FALSE needed")
  
  if (!is.character(FUN))
    stop("only '+', '-', '*', and '/' are implemented for floats")
  
  FUN = match.arg(FUN, c('+', '-', '*', '/'))
  
  if (isTRUE(check.margin))
  {
    if ((MARGIN == 1 && NROW(x)%%length(STATS)) || (MARGIN == 2 && NCOL(x)%%length(STATS)))
      warning("STATS does not recycle exactly across MARGIN")
  }
  
  ret = .Call(R_sweep_spm, DATA(x), as.integer(MARGIN), STATS, FUN)
  float32(ret)
}



#' @rdname sweep
#' @export
setMethod("sweep", signature(x="float32"), sweep_float32)
