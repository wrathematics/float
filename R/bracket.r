bracket.spm = function(x, i, j)
{
  if (missing(i) && missing(j))
    return(x)
  
  if (missing(i))
    i = 1:nrow(x)
  else
  {
    if (!is.numeric(i) && !is.logical(i))
      stop(paste0("invalid subscript type '", typeof(i), "'"))
    
    if (is.double(i))
      storage.mode(i) = "integer"
  }
  
  if (missing(j))
  {
    if (!isavec(x))
      j = 1:ncol(x)
    else
      stop("incorrect number of dimensions")
  }
  else
  {
    if (!is.numeric(j) && !is.logical(j))
      stop(paste("invalid subscript type", typeof(j)))
    
    if (is.double(j))
      storage.mode(j) = "integer"
  }
  
  ptr = .Call(R_bracket_spm, x@ptr, i, j)
  new("spm", ptr=ptr)
}

#' @rdname bracket
#' @export
setMethod("[", signature(x="spm"), bracket.spm)
