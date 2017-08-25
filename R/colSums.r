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
#' \dontrun{
#' library(float)
#' 
#' s = flrunif(5, 3)
#' 
#' rowSums(s)
#' colSums(s)
#' }
#' 
#' @name colsums
#' @rdname colsums
NULL



colSums.spm = function(x, na.rm=FALSE, dims=1)
{
  ptr = .Call(R_colSums_spm, x@ptr, na.rm)
  new("spm", ptr=ptr)
}

rowSums.spm = function(x, na.rm=FALSE, dims=1)
{
  ptr = .Call(R_rowSums_spm, x@ptr, na.rm)
  new("spm", ptr=ptr)
}

colMeans.spm = function(x, na.rm=FALSE, dims=1)
{
  ptr = .Call(R_colMeans_spm, x@ptr, na.rm)
  new("spm", ptr=ptr)
}

rowMeans.spm = function(x, na.rm=FALSE, dims=1)
{
  ptr = .Call(R_rowMeans_spm, x@ptr, na.rm)
  new("spm", ptr=ptr)
}



#' @rdname colsums
#' @export
setMethod("colSums", signature(x="spm"), colSums.spm)

#' @rdname colsums
#' @export
setMethod("rowSums", signature(x="spm"), rowSums.spm)

#' @rdname colsums
#' @export
setMethod("colMeans", signature(x="spm"), colMeans.spm)

#' @rdname colsums
#' @export
setMethod("rowMeans", signature(x="spm"), rowMeans.spm)
