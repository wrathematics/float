#' print-spm
#' 
#' Print methods for float vector/matrices.
#' 
#' @param x,object
#' A float vector/matrix.
#' @param ...
#' Ignored.
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' 
#' s = flrunif(10, 3)
#' print(s)
#' s
#' }
#' 
#' @name print-spm
#' @rdname print-spm
NULL



print_spm_vec = function(x)
{
  n = NROW(x)
  
  cat(paste0("# An spv (single precision vector): ", n, "\n"))
  
  top = min(5, n)
  if (top == 0)
  {
    cat("# [no elements to display]\n")
    return(invisible())
  }
  
  if (top == n)
    submat = spm2mat(x)
  else
    submat = spm2mat(x[1:top])
  
  dim(submat) = NULL
  
  if (top < n)
    cat(capture.output(submat), "... \n")
  else
    print(submat) # NOTE intentional
  
  invisible()
}



print_spm_mat = function(x)
{
  m = NROW(x)
  n = NCOL(x)
  
  cat(paste0("# An spm (single precision matrix): ", m, "x", n, "\n"))
  
  toprow = min(10, m)
  topcol = min(5, n)
  if (toprow == 0 || topcol == 0)
  {
    cat("# [no elements to display]\n")
    return(invisible())
  }
  
  if (toprow == m && toprow == n)
    submat = spm2mat(x)
  else
    submat = spm2mat(x[1:toprow, 1:topcol, drop=FALSE])
  
  submat = submat[1:toprow, 1:topcol, drop=FALSE]
  
  print(submat) # NOTE intentional
  
  if (toprow < m || topcol < n)
    cat("# ...\n\n")
  
  invisible()
}



print_attr = function(x)
{
  att = attributes(x)
  att$ptr = NULL
  att$class = NULL
  
  if (length(att) == 0)
    return(invisible())
  
  for (i in 1:length(att))
  {
    cat(paste0("attr(,\"", names(att)[i], "\")\n"))
    print(att[[i]]) # NOTE intentional
  }
}



print_spm = function(x)
{
  if (isavec(x))
    print_spm_vec(x)
  else
    print_spm_mat(x)
  
  print_attr(x)
}



#' @rdname print-spm
#' @export
setMethod("print", signature(x="spm"), function(x, ...) print_spm(x))

#' @rdname print-spm
#' @export
setMethod("show", signature(object="spm"), function(object) print_spm(object))
