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



#' @export
setMethod("%*%", signature(x="spm", y="spm"), mm.spm)

#' @export
setMethod("%*%", signature(x="spm", y="matrix"), mm.spm_mat)

#' @export
setMethod("%*%", signature(x="matrix", y="spm"), mm.mat_spm)
