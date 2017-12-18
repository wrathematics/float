#' print-float32
#' 
#' Print methods for float vector/matrices.
#' 
#' @param x,object
#' A float vector/matrix.
#' @param ...
#' Ignored.
#' 
#' @examples
#' library(float)
#' 
#' s = flrunif(10, 3)
#' print(s)
#' s
#' 
#' @name print-float32
#' @rdname print-float32
NULL



print_float_vec = function(x)
{
  n = NROW(x)
  
  cat(paste0("# A float32 vector: ", n, "\n"))
  
  top = min(5, n)
  if (top == 0)
  {
    cat("# [no elements to display]\n")
    return(invisible())
  }
  
  if (top == n)
    submat = dbl(x)
  else
    submat = dbl(x[1:top])
  
  if (top < n)
    cat(capture.output(submat), "... \n")
  else
    print(submat) # NOTE intentional
  
  invisible()
}



print_float_mat = function(x)
{
  m = NROW(x)
  n = NCOL(x)
  
  cat(paste0("# A float32 matrix: ", m, "x", n, "\n"))
  
  toprow = min(10, m)
  topcol = min(5, n)
  if (toprow == 0 || topcol == 0)
  {
    cat("# [no elements to display]\n")
    return(invisible())
  }
  
  if (toprow == m && toprow == n)
    submat = dbl(x)
  else
    submat = dbl(x[1:toprow, 1:topcol, drop=FALSE])
  
  submat = submat[1:toprow, 1:topcol, drop=FALSE]
  
  print(submat) # NOTE intentional
  
  if (toprow < m || topcol < n)
    cat("# ...\n\n")
  
  invisible()
}



print_attr = function(x)
{
  att = attributes(x)
  att$Data = NULL
  att$class = NULL
  
  if (length(att) == 0)
    return(invisible())
  
  for (i in 1:length(att))
  {
    cat(paste0("attr(,\"", names(att)[i], "\")\n"))
    print(att[[i]]) # NOTE intentional
  }
}



print_float32 = function(x)
{
  if (isavec(x))
    print_float_vec(x)
  else
    print_float_mat(x)
  
  print_attr(x)
}

#' @rdname print-float32
#' @export
setMethod("print", signature(x="float32"), function(x, ...) print_float32(x))

#' @rdname print-float32
#' @export
setMethod("show", signature(object="float32"), function(object) print_float32(object))
