#' @export
setMethod("nrow", signature(x="spm"), function(x) .Call(R_nrow_spm, x@ptr))

#' @export
setMethod("ncol", signature(x="spm"), function(x) .Call(R_ncol_spm, x@ptr))

#' @export
setMethod("dim", signature(x="spm"), function(x) .Call(R_dim_spm, x@ptr))



# for my eyes only
isavec = function(x) .Call(R_isavec_spm, x@ptr)
