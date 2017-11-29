#' colSums
#' 
#' Row and columns sums/means.
#' 
#' @param x
#' A float vector/matrix.
#' @param na.rm
#' Should missing values be removed?
#' @param dims
#' Ignored. Be honest, you've never even used this argument before, have you?
#' 
#' @return
#' A matrix of the same type as the highest precision input.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(5, 3)
#' 
#' rowSums(s)
#' colSums(s)
#' 
#' @name colsums
#' @rdname colsums
NULL



colSums_float32 = function(x, na.rm=FALSE, dims=1)
{
  ret = .Call(R_colSums_spm, DATA(x), na.rm)
  float32(ret)
}

rowSums_float32 = function(x, na.rm=FALSE, dims=1)
{
  ret = .Call(R_rowSums_spm, DATA(x), na.rm)
  float32(ret)
}

colMeans_float32 = function(x, na.rm=FALSE, dims=1)
{
  ret = .Call(R_colMeans_spm, DATA(x), na.rm)
  float32(ret)
}

rowMeans_float32 = function(x, na.rm=FALSE, dims=1)
{
  ret = .Call(R_rowMeans_spm, DATA(x), na.rm)
  float32(ret)
}



#' @rdname colsums
#' @export
setMethod("colSums", signature(x="float32"), colSums_float32)

#' @rdname colsums
#' @export
setMethod("rowSums", signature(x="float32"), rowSums_float32)

#' @rdname colsums
#' @export
setMethod("colMeans", signature(x="float32"), colMeans_float32)

#' @rdname colsums
#' @export
setMethod("rowMeans", signature(x="float32"), rowMeans_float32)
