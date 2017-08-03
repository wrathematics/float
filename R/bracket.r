#' Extract
#' 
#' Extract subsets of a float vector/matrix.
#' 
#' @param x
#' A float vector/matrix.
#' @param i,j
#' The indices. NOTE that at this time only non-specified and positive indexed
#' i/j are accepted.
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



bracket.spm = function(x, i, j, drop=TRUE)
{
  drop = ifelse(isTRUE(drop[1]), TRUE, FALSE)
  
  if (missing(i) && missing(j))
    return(x)
  
  if (isavec(x))
  {
    if (!missing(j))
      stop("incorrect number of dimensions")
  }
  
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
    j = 1:ncol(x)
  else
  {
    if (!is.numeric(j) && !is.logical(j))
      stop(paste("invalid subscript type", typeof(j)))
    
    if (is.double(j))
      storage.mode(j) = "integer"
  }
  
  ptr = .Call(R_bracket_spm, x@ptr, i, j, drop)
  new("spm", ptr=ptr)
}



#' @rdname bracket
#' @export
setMethod("[", signature(x="spm"), bracket.spm)
