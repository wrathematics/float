diag.spm = function(x, nrow, ncol)
{
  if (missing(nrow) && missing(ncol))
  {
    if (isavec(x))
    {
      len = as.integer(spm::nrow(x))
      ptr = .Call(R_diagmat_spm, x@ptr, len, len)
    }
    else
      ptr = .Call(R_diag_spm, x@ptr)
  }
  else
  {
    if (!isavec(x))
      stop("'nrow' or 'ncol' cannot be specified when 'x' is a matrix")
    
    if (missing(nrow))
      nrow = ncol
    else if (missing(ncol))
      ncol = nrow
    
    ptr = .Call(R_diagmat_spm, x@ptr, as.integer(nrow), as.integer(ncol))
  }
  
  new("spm", ptr=ptr)
}



#' @export
setMethod("diag", signature(x="spm"), diag.spm)
