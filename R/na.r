#' NA
#' 
#' NA utilities.
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
#' is.na(s)
#' 
#' @name na
#' @rdname na
NULL



is.na_float32 = function(x)
{
  .Call(R_isna_spm, DATA(x))
}

na.omit_float32 = function(object, ...)
{
  ret = .Call(R_naomit_spm, DATA(object))
  float32(ret)
}



#' @rdname na
#' @export
setMethod("is.na", signature(x="float32"), is.na_float32)

#' @rdname na
#' @export
setMethod("na.omit", signature(object="float32"), na.omit_float32)

#' @rdname na
#' @export
setMethod("na.exclude", signature(object="float32"), na.omit_float32)



# -----------------------------------------------------------------------------
# internal only
# -----------------------------------------------------------------------------

anyNA = function(x)
{
  .Call(R_anyNA_spm, DATA(x))
}
