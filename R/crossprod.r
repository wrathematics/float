cp.spm = function(x, y=NULL)
{
  if (is.spm(x))
  {
    if (is.null(y))
      ptr = .Call(R_crossprod_spm, x@ptr)
    else if (is.spm(y))
      ptr = .Call(R_crossprod_spmspm, x@ptr, y@ptr)
    else if (is.matrix(y))
      return(base::crossprod(spm2mat(x), y))
    else
      stop("TODO")
  }
  else if (is.matrix(x) && is.spm(y))
    return(base::crossprod(x, spm2mat(y)))
  else
    return(base::crossprod(x, y))
  
  new("spm", ptr=ptr)
}

tcp.spm = function(x, y=NULL)
{
  if (is.spm(x))
  {
    if (is.null(y))
      ptr = .Call(R_tcrossprod_spm, x@ptr)
    else if (is.spm(y))
      ptr = .Call(R_tcrossprod_spmspm, x@ptr, y@ptr)
    else if (is.matrix(y))
      return(base::tcrossprod(spm2mat(x), y))
    else
      stop("TODO")
  }
  else if (is.matrix(x) && is.spm(y))
    return(base::tcrossprod(x, spm2mat(y)))
  else
    return(base::tcrossprod(x, y))
  
  new("spm", ptr=ptr)
}



#' @export
setMethod("crossprod", signature(x="mat", y="ANY"), cp.spm)

#' @export
setMethod("tcrossprod", signature(x="mat", y="ANY"), tcp.spm)
