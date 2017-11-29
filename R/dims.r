#' dim
#' 
#' Dimension information for a float vector/matrix.
#' 
#' @param x
#' A float vector/matrix.
#' @param value
#' The right hand side for the "setter" (\code{dim<-}).
#' 
#' @return
#' The requested integer values.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' dim(s)
#' nrow(s)
#' ncol(s)
#' 
#' @name dims
#' @rdname dims
NULL



DATA = function(x) x@Data
isavec = function(x) !is.matrix(DATA(x))



#' @rdname dims
#' @export
setMethod("nrow", signature(x="float32"), function(x) NROW(DATA(x)))

#' @rdname dims
#' @export
setMethod("ncol", signature(x="float32"), function(x) NCOL(DATA(x)))

#' @rdname dims
#' @export
setMethod("NROW", signature(x="float32"), function(x) NROW(DATA(x)))

#' @rdname dims
#' @export
setMethod("NCOL", signature(x="float32"), function(x) NCOL(DATA(x)))

#' @rdname dims
#' @export
setMethod("dim", signature(x="float32"), function(x) c(nrow(x), ncol(x)))

#' @rdname dims
#' @export
setMethod("length", signature(x="float32"), function(x) nrow(x)*ncol(x))



dimset_float32 = function(x, value)
{
  dim(x@Data) = value
  x
}

#' @rdname dims
#' @export
setReplaceMethod("dim", signature(x="float32"), dimset_float32)
