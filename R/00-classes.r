setClassUnion("Int", c("integer", "matrix"))

#' Class float32
#' 
#' An S4 container for single precision (float) vector/matrix objects.
#' 
#' @slot ptr
#' An external pointer to a struct.
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
