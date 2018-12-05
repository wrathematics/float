#' scale
#' 
#' Center/scale a float vector/matrix.
#' 
#' @details
#' Only logical \code{center} and \code{scale} parameters are accepted at this
#' time.
#' 
#' @param x
#' A float vector/matrix.
#' @param center,scale
#' Logical
#' 
#' @return
#' A float matrix.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' scale(s)
#' 
#' @useDynLib float R_scale_spm
#' @name scale
#' @rdname scale
NULL



scale_float32 = function(x, center=TRUE, scale=TRUE) 
{
  if (is.na(center) || is.na(scale))
    stop("missing value where TRUE/FALSE needed")
  
  if (!is.logical(center))
  {
    if (length(center) != ncol(x))
      stop("length of 'center' must equal the number of columns of 'x'")
    
    x = sweep(x, MARGIN=2, STATS=center, FUN="-")
    center = FALSE
  }
  if (!is.logical(scale))
  {
    if (length(scale) != ncol(x))
      stop("length of 'scale' must equal the number of columns of 'x'")
    
    x = sweep(x, MARGIN=2, STATS=scale, FUN="-")
    scale = FALSE
  }
  
  if (!isTRUE(center) && !isTRUE(scale))
    return(x)
  
  .Call(R_scale_spm, DATA(x), as.integer(center), as.integer(scale))
}



#' @rdname scale
#' @export
setMethod("scale", signature(x="float32"), scale_float32)
