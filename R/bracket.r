#' Extract
#' 
#' Extract subsets of a float vector/matrix.
#' 
#' @param x
#' A float vector/matrix.
#' @param i,j
#' The indices.  Most combinations of integer/double/logical values will be
#' treated the same as R does. One major difference is that \code{NA} values
#' will not be tolerated.
#' @param drop
#' Logical. If TRUE, single column matrices will be treated as one-dimensional
#' vectors.
#' 
#' @return
#' A float vector/matrix.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' s = flrunif(10, 3)
#' s[, -1]
#' s[c(1, 3, 5, 7), 1:2]
#' }
#' 
#' @name bracket
#' @rdname bracket
NULL



bracket_float32 = function(x, i, j, drop=TRUE)
{
  if (missing(i) && missing(j))
    return(x)
  
  d = DATA(x)
  dim(d) = c(nrow(x), ncol(x))
  d = d[i, j, drop=drop]
  
  new("float32", Data=d)
}



#' @rdname bracket
#' @export
setMethod("[", signature(x="float32"), bracket_float32)
