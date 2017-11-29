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
#' @name scale
#' @rdname scale
NULL



scale_float32 = function(x, center=TRUE, scale=TRUE) 
{
  if (!is.logical(center) || !is.logical(scale))
    stop("only logical 'center' and 'scale' implemented at this time")
  
  if (is.na(center) || is.na(scale))
    stop("missing value where TRUE/FALSE needed")
  
  if (!isTRUE(center) && !isTRUE(scale))
    return(x)
  
  .Call(R_scale_spm, DATA(x), as.integer(center), as.integer(scale))
}



#' @rdname scale
#' @export
setMethod("scale", signature(x="float32"), scale_float32)
