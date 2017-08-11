#' sum
#' 
#' Sums the elements of a shaq.
#' 
#' @details
#' TODO
#' 
#' @param x
#' 
#' @param ...
#' Additional elements (shaqs or numeric vectors/matrices) to sum.  Regular
#' vectors/matrices are assumed to be global, but will only be included to the
#' sum on rank 0.
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
    if (any(sapply(additional, function(x) is.double(x))))
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
