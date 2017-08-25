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
#' \dontrun{
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
#' }
#' 
#' @name matmult
#' @rdname matmult
NULL



mm.spm = function(x, y)
{
  ptr = .Call(R_matmult_spm, x@ptr, y@ptr)
  new("spm", ptr=ptr)
}

mm.spm_mat = function(x, y)
{
  if (is.integer(y))
    x %*% mat2spm(y)
  else if (is.double(y))
    spm2mat(x) %*% y
  else
    stop("TODO")
}

mm.mat_spm = function(x, y)
{
  if (is.integer(x))
    mat2spm(x) %*% y
  else if (is.double(x))
    x %*% spm2mat(y)
  else
    stop("TODO")
}



#' @rdname matmult
#' @export
setMethod("%*%", signature(x="spm", y="spm"), mm.spm)

#' @rdname matmult
#' @export
setMethod("%*%", signature(x="spm", y="matrix"), mm.spm_mat)

#' @rdname matmult
#' @export
setMethod("%*%", signature(x="matrix", y="spm"), mm.mat_spm)
