#' c
#' 
#' Combine float/numeric vector(s)/matri[x|ces].
#' 
#' @param x
#' A float matrix.
#' @param ...
#' Additional elements (numeric/float vectors/matrices) to sum.
#'  
#' @return 
#' TODO
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' x = flrunif(10, 3)
#' 
#' c(x, NA, 1L)
#' }
#' 
#' @name c
#' @rdname c
NULL



c_spm = function(x, additional)
{
  ptr = .Call(R_c_spm, x@ptr, additional)
  new("spm", ptr=ptr)
}

c.spm = function(x, ...)
{
  additional = list(...)
  
  if (length(additional) == 0)
    return(x)
  
  if (any(sapply(additional, function(x) is.double(x))))
  {
    x = dbl(x)
    additional = lapply(additional, dbl, strict=FALSE)
    
    do.call(base::c, list(x, additional))
  }
  else
  {
    additional = lapply(additional, fl, strict=FALSE)
    ptr = c_spm(x, additional)
    new("spm", ptr)
  }
}



#' @rdname c
#' @export
setMethod("c", signature(x="spm"), c.spm)
