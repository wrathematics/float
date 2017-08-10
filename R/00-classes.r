#' Class spm
#' 
#' An S4 container for single precision (float) vector/matrix objects.
#' 
#' @slot ptr
#' An external pointer to a struct.
#' 
#' @name spm-class
#' @docType class
#' 
#' @export
setClass("spm", 
  representation(ptr="externalptr")
)



setClassUnion("Mat", c("matrix", "spm"))
setClassUnion("BaseLinAlg", c("matrix", "vector"))
