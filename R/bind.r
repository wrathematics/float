#' rbind
#' 
#' \code{rbind()} and \code{cbind()} for floats.
#' 
#' @param ... 
#' vectors or matrices (numeric or float)
#' @param deparse.level 
#' ignored
#' 
#' @return 
#' A matrix of the same type as the highest precision input.
#' 
#' @examples
#' library(float)
#' x = fl(matrix(1:10, 5))
#' 
#' rbind(x, x)
#' cbind(x, x)
#' 
#' @name bind
#' @rdname bind
NULL



bind_float32 = function(binder, ..., deparse.level)
{
  args = list(...)
  
  if (any(sapply(args, is.double)))
  {
    args = lapply(args, dbl, strict=FALSE)
   
   do.call(binder, args) 
  }
  else
  {
    raw = lapply(args, function(x) DATA(fl(x, strict=FALSE)))
    ret = do.call(binder, raw)
    float32(ret)
  }
}



#' @method rbind float32
#' @rdname bind
#' @export
rbind.float32 <- function(..., deparse.level=1)
{
  bind_float32(base::rbind, ..., deparse.level=deparse.level)
}

#' @method cbind float32
#' @rdname bind
#' @export
cbind.float32 <- function(..., deparse.level=1)
{
  bind_float32(base::cbind, ..., deparse.level=deparse.level)
}
