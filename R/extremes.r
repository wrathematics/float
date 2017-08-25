#' extremes
#' 
#' Min/max values for any combination of float/numeric vector(s)/matri[x|ces].
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
#' library(float)
#' x = flrunif(10, 3)
#' 
#' min(x)
#' min(x, 1)
#' }
#' 
#' @name extremes
#' @rdname extremes
NULL



min_spm = function(x, na.rm)
{
  ptr = .Call(R_min_spm, x@ptr, na.rm)
  new("spm", ptr=ptr)
}

max_spm = function(x, na.rm)
{
  ptr = .Call(R_max_spm, x@ptr, na.rm)
  new("spm", ptr=ptr)
}

extremer = function(x, na.rm, dFUN, sFUN)
{
  if (is.spm(x))
    dbl(sFUN(x, na.rm=na.rm))
  else
    dFUN(x, na.rm=na.rm)
}

extreme = function(x, ..., na.rm=FALSE, dFUN, sFUN)
{
  additional = list(...)
  first = sFUN(x, na.rm=na.rm)
  
  if (length(additional) > 0)
  {
    additional = dFUN(sapply(additional, extremer, na.rm=na.rm, dFUN=dFUN, sFUN=sFUN))
    if (any(sapply(additional, is.double)))
      dFUN(dbl(first),  additional)
    else
    {
      additional = fl(additional)
      sFUN(c(first, additional), na.rm=na.rm)
    }
  }
  else
    first
}

min.spm = function(x, ..., na.rm=FALSE)
{
  extreme(x, ..., na.rm=na.rm, dFUN=base::min, sFUN=min_spm)
}

max.spm = function(x, ..., na.rm=FALSE)
{
  extreme(x, ..., na.rm=na.rm, dFUN=base::max, sFUN=max_spm)
}

whichmin.spm = function(x)
{
  .Call(R_whichmin_spm, x@ptr)
}

whichmax.spm = function(x)
{
  .Call(R_whichmax_spm, x@ptr)
}



#' @rdname extremes
#' @export
setMethod("min", signature(x="spm"), min.spm)

#' @rdname extremes
#' @export
setMethod("max", signature(x="spm"), max.spm)

#' @rdname extremes
#' @export
setMethod("which.min", signature(x="spm"), whichmin.spm)

#' @rdname extremes
#' @export
setMethod("which.max", signature(x="spm"), whichmax.spm)
