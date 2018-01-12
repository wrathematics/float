#' @export
str.float32 = function(object, digits.d=strO$digits.d, ...)
{
  strO = utils::strOptions()
  MAXLEN = 10L
  len = length(object)
  printlen = min(len, MAXLEN)
  
  # this is hideous, but I don't think there's any way to play the same game with S4
  s = DATA(object)[1:printlen, drop=TRUE]
  vals = dbl(float32(s))
  
  cat("Formal class 'float32' [package \"float\"] with 1 slot\n")
  
  if (isavec(object))
    cat(paste0("..@ Data: int [1:", len, "] "))
  else
    cat(paste0("..@ Data: int [1:", nrow(object), ", 1:", ncol(object), "] "))
  
  cat(format(vals, digits=digits.d))
  if (length(vals) < length(object))
    cat(" ...")
  
  cat("\n")
  
  invisible()
}
