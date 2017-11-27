setClassUnion("Int", c("integer", "matrix"))

#' Class float32
#' 
#' An S4 container for 32-bit float vector/matrix objects.
#' 
#' @slot Data
#' A vector or matrix of integers.
#' 
#' @name float32-class
#' @docType class
#' 
#' @export
setClass("float32", 
  representation(
    Data="Int"
  )
)

setClassUnion("Mat", c("matrix", "float32"))
setClassUnion("BaseLinAlg", c("matrix", "vector"))
