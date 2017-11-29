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
#' library(float)
#' x = flrunif(10, 3)
#' 
#' min(x)
#' min(x, 1)
#' 
#' @name extremes
#' @rdname extremes
NULL



min_float32_ = function(x, na.rm)
{
  ret = .Call(R_min_spm, DATA(x), na.rm)
  float32(ret)
}

max_float32_ = function(x, na.rm)
{
  ret = .Call(R_max_spm, DATA(x), na.rm)
  float32(ret)
}

extremer = function(x, na.rm, dFUN, sFUN)
{
  if (is.float(x))
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

min_float32 = function(x, ..., na.rm=FALSE)
{
  extreme(x, ..., na.rm=na.rm, dFUN=base::min, sFUN=min_float32_)
}

max_float32 = function(x, ..., na.rm=FALSE)
{
  extreme(x, ..., na.rm=na.rm, dFUN=base::max, sFUN=max_float32_)
}

whichmin_float32 = function(x)
{
  .Call(R_whichmin_spm, DATA(x))
}

whichmax_float32 = function(x)
{
  .Call(R_whichmax_spm, DATA(x))
}



#' @rdname extremes
#' @export
setMethod("min", signature(x="float32"), min_float32)

#' @rdname extremes
#' @export
setMethod("max", signature(x="float32"), max_float32)

#' @rdname extremes
#' @export
setMethod("which.min", signature(x="float32"), whichmin_float32)

#' @rdname extremes
#' @export
setMethod("which.max", signature(x="float32"), whichmax_float32)
