#' @export
setClass("spm", 
  representation(ptr="externalptr")
)

setClassUnion("mat", c("matrix", "spm"))
