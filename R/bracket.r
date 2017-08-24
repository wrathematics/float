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
#' library(spm)
#' 
#' s = flrunif(10, 3)
#' s[, -1]
#' s[c(1, 3, 5, 7), 1:2]
#' }
#' 
#' @name bracket
#' @rdname bracket
NULL



bracket_check = function(ind)
{
  .Call(R_bracketchecks_spm, ind)
}

bracket_lgl2int = function(len, ind)
{
  if (len == length(ind))
    which(ind)
  else
    c(which(ind), (length(ind)+1L):len)
}

bracket.spm = function(x, i, j, drop=TRUE)
{
  drop = ifelse(isTRUE(as.logical(drop[1])), TRUE, FALSE)
  
  if (missing(i) && missing(j))
    return(x)
  
  if (isavec(x))
  {
    if (!missing(j))
      stop("incorrect number of dimensions")
  }
  
  if (missing(i))
    i = 1:NROW(x)
  else
  {
    if (is.double(i))
      storage.mode(i) = "double"
    
    has0 = bracket_check(i)
    if (has0)
      i = i[which(i != 0)]
    
    if (is.logical(i))
      i = bracket_lgl2int(nrow(x), i)
  }
  
  if (missing(j))
    j = 1:NCOL(x)
  else
  {
    if (is.double(j))
      storage.mode(j) = "double"
    
    has0 = bracket_check(j)
    if (has0)
      j = j[which(j != 0)]
    
    if (is.logical(j))
      j = bracket_lgl2int(ncol(x), j)
  }
  
  ptr = .Call(R_bracket_spm, x@ptr, i, j, drop)
  new("spm", ptr=ptr)
}



#' @rdname bracket
#' @export
setMethod("[", signature(x="spm"), bracket.spm)
