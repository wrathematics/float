#' names
#' 
#' "name" setter/getters.
#' 
#' @param x
#' A float vector/matrix.
#' @param value
#' Replacement value.
#' 
#' @name names
#' @rdname names
NULL

names_get_float32 = function(x)
{
  names(DATA(x))
}

#' @rdname names
#' @export
setMethod("names", signature(x="float32"), names_get_float32)

names_set_float32 = function(x, value)
{
  names(x@Data) = value
  x
}

#' @rdname names
#' @export
setReplaceMethod("names", signature(x="float32"), names_set_float32)



rownames_get_float32 = function(x)
{
  rownames(DATA(x))
}

#' @rdname names
#' @export
setMethod("rownames", signature(x="float32"), rownames_get_float32)

rownames_set_float32 = function(x, value)
{
  rownames(x@Data) = value
  x
}

#' @rdname names
#' @export
setReplaceMethod("rownames", signature(x="float32"), rownames_set_float32)



colnames_get_float32 = function(x)
{
  colnames(DATA(x))
}

#' @rdname names
#' @export
setMethod("colnames", signature(x="float32"), colnames_get_float32)

colnames_set_float32 = function(x, value)
{
  colnames(x@Data) = value
  x
}

#' @rdname names
#' @export
setReplaceMethod("colnames", signature(x="float32"), colnames_set_float32)



dimnames_get_float32 = function(x)
{
  dimnames(DATA(x))
}

#' @rdname names
#' @export
setMethod("dimnames", signature(x="float32"), dimnames_get_float32)

dimnames_set_float32 = function(x, value)
{
  dimnames(x@Data) = value
  x
}

#' @rdname names
#' @export
setReplaceMethod("dimnames", signature(x="float32"), dimnames_set_float32)
