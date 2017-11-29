#' c
#' 
#' Combine float/numeric vector(s)/matri[x|ces].
#' 
#' @param x
#' A float matrix.
#' @param ...
#' Additional elements (numeric/float vectors/matrices) to sum.
#'  
#' @return 
#' A matrix of the same type as the highest precision input.
#' 
#' @examples
#' library(float)
#' x = flrunif(10, 3)
#' 
#' c(x, NA, 1L)
#' 
#' @name c
#' @rdname c
NULL



c_float32 = function(x, ...)
{
  additional = list(...)
  
  if (length(additional) == 0)
    return(x)
  
  if (any(sapply(additional, is.double)))
  {
    x = dbl(x)
    additional = lapply(additional, dbl, strict=FALSE)
    
    unlist(list(x, additional))
  }
  else
  {
    raw = lapply(additional, function(x) DATA(fl(x, strict=FALSE)))
    ret = c(DATA(x), do.call(c, raw))
    float32(ret)
  }
}



#' @rdname c
#' @export
setMethod("c", signature(x="float32"), c_float32)
