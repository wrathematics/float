#' @export
str.float32 = function(object, digits.d=strO$digits.d, ...)
{
  strO = utils::strOptions()
  MAXLEN = 10L
  
  vals = dbl(object[1:(min(length(object), MAXLEN)), 1, drop=TRUE])
  cat("Formal class 'float32' [package \"float\"] with 1 slot\n")
  cat(paste0("..@ Data: int [1:", length(object), "] "))
  cat(format(vals, digits=digits.d))
  if (length(vals) < length(object))
    cat(" ...")
  
  cat("\n")
  
  invisible()
}
