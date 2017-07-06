print_spm = function(x)
{
  m = nrow(x)
  n = ncol(x)
  
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
    submat = spm2mat(x[1:toprow, 1:topcol])
  
  print(submat) # NOTE intentional
  
  if (toprow < nrow(x) || topcol < ncol(x))
    cat("# ...\n\n")
  
  invisible()
}



#' @rdname print
#' @export
setMethod("print", signature(x="spm"), function(x, ...) print_spm(x))

#' @rdname print
#' @export
setMethod("show", signature(object="spm"), function(object) print_spm(object))
