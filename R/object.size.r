#' object.size
#' 
#' Return the memory being used to store the object.
#' 
#' @param x
#' A float vector/matrix.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' s = flrunif(10, 3)
#' object.size(s)
#' 
#' ### if the memuse package is also available:
#' library(memuse)
#' memuse(s)
#' }
#' 
#' @name object.size
#' @rdname object_size
NULL



numbytes.spm = function(x)
{
  .Call(R_numbytes_spm, x@ptr) + utils::object.size(x)
}



#' @rdname object_size
#' @export
setMethod("object.size", signature(x="spm"), numbytes.spm)



####' @importMethodsFrom memuse memuse mu
# #' @rdname object_size
# #' @export
# setMethod("mu", signature(size="spm"),
#   function(size, unit="best", prefix="IEC", names="short")
#   {
#     size = unclass(spm::object.size(size))
#     memuse::mu(size, unit=unit, prefix=prefix, names=names)
#   }
# )

# #' @rdname object_size
# #' @export
# setMethod("memuse", signature(size="spm"),
#   function(size, unit="best", prefix="IEC", names="short")
#   {
#     size = unclass(spm::object.size(size))
#     memuse::mu(size, unit=unit, prefix=prefix, names=names)
#   }
# )
