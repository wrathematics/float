#' sum
#' 
#' Sums any combination of float/numeric vector(s)/matri[x|ces].
#' 
#' @details
#' If there are any elements in \code{...}, all elements in the list will first
#' be summed in their native precision, then converted to double precision so
#' they can be combined with \code{base::sum()}.  The final result will be cast
#' to single precision if \code{...} contains only integer and/or float objects.
#' Otherwise, the return will be double precision.
#' 
#' @param x
#' A float matrix.
#' @param ...
#' Additional elements (numeric/float vectors/matrices) to sum.
#' @param na.rm
#' should NA's be removed?
#'  
#' @return 
#' A single value.
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' x = flrunif(10, 3)
#' 
#' sum(x)
#' sum(x, 1)
#' }
#' 
#' @name sum
#' @rdname sum
NULL



sum_spm = function(x, na.rm)
{
  ptr = .Call(R_sum_spm, x@ptr, na.rm)
  new("spm", ptr=ptr)
}

summer = function(x, na.rm)
{
  if (is.spm(x))
    dbl(sum_spm(x, na.rm=na.rm))
  else
    sum(x, na.rm=na.rm)
}

sum.spm = function(x, ..., na.rm=FALSE)
{
  additional = list(...)
  xsum = sum_spm(x, na.rm=na.rm)
  
  if (length(additional) > 0)
  {
    additional_sum = base::sum(sapply(additional, summer, na.rm=na.rm))
    if (any(sapply(additional, is.double)))
      dbl(xsum) + additional_sum
    else
      xsum + fl(additional_sum)
  }
  else
    xsum
}



#' @rdname sum
#' @export
setMethod("sum", signature(x="spm"), sum.spm)
