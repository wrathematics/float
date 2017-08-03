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
#' \dontrun{
#' library(spm)
#' 
#' s = flrunif(10, 3)
#' is.na(s)
#' }
#' 
#' @name na
#' @rdname na
NULL



is.na.spm = function(x)
{
  .Call(R_isna_spm, x@ptr)
}

na.omit.spm = function(object, ...)
{
  ptr = .Call(R_naomit_spm, object@ptr)
  new("spm", ptr=ptr)
}



#' @rdname na
#' @export
setMethod("is.na", signature(x="spm"), is.na.spm)

#' @rdname na
#' @export
setMethod("na.omit", signature(object="spm"), na.omit.spm)

#' @rdname na
#' @export
setMethod("na.exclude", signature(object="spm"), na.omit.spm)
