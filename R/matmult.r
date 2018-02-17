#' matmult
#' 
#' Matrix multiplication for numeric/float matrices.
#' 
#' @details
#' If a numeric matrix is multiplied against a float matrix, then if the
#' "numeric" matrix is integers, the integers are promoted to floats. Otherwise,
#' the float matrix is promoted to doubles.
#' 
#' @param x,y
#' Numeric/float matrices.
#' 
#' @return
#' A matrix of the same type as the highest precision input.
#' 
#' @examples
#' library(float)
#' 
#' s1 = flrunif(5, 5)
#' s2 = flrunif(5, 2)
#' x = matrix(1:25, 5)
#' 
#' s1 %*% s2 # float
#' 
#' storage.mode(x) # integer
#' x %*% s2 # float
#' 
#' storage.mode(x) = "double"
#' x %*% s2 # double
#' 
#' @name matmult
#' @rdname matmult
NULL



mm_float32 = function(x, y)
{
  ret = .Call(R_matmult_spm, DATA(x), DATA(y))
  float32(ret)
}

mm_float32_mat = function(x, y)
{
  if (is.integer(y))
    x %*% fl(y)
  else if (is.double(y))
    dbl(x) %*% y
  else
    stop("requires numeric/complex matrix/vector arguments")
}

mm_mat_float32 = function(x, y)
{
  if (is.integer(x))
    fl(x) %*% y
  else if (is.double(x))
    x %*% dbl(y)
  else
    stop("requires numeric/complex matrix/vector arguments")
}



#' @rdname matmult
#' @export
setMethod("%*%", signature(x="float32", y="float32"), mm_float32)

#' @rdname matmult
#' @export
setMethod("%*%", signature(x="float32", y="matrix"), mm_float32_mat)

#' @rdname matmult
#' @export
setMethod("%*%", signature(x="matrix", y="float32"), mm_mat_float32)
