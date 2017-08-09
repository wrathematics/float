#' arithmetic
#' 
#' Binary arithmetic numeric/float matrices.
#' 
#' @param e1,e2
#' Numeric/float vectors/matrices.
#' 
#' @return
#' A matrix of the same type as the highest precision input.
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' 
#' s1 = flrunif(5, 5)
#' s2 = flrunif(5, 2)
#' x = matrix(1:25, 5)
#' 
#' s1 + s2 # float
#' 
#' storage.mode(x) # integer
#' x + s2 # float
#' 
#' storage.mode(x) = "double"
#' x + s2 # double
#' }
#' 
#' @name arithmetic
#' @rdname arithmetic
NULL



add_spmspm = function(e1, e2)
{
  ptr = .Call(R_add_spm, e1@ptr, e2@ptr)
  new("spm", ptr=ptr)
}

mul_spmspm = function(e1, e2)
{
  ptr = .Call(R_mul_spm, e1@ptr, e2@ptr)
  new("spm", ptr=ptr)
}

sub_spmspm = function(e1, e2)
{
  ptr = .Call(R_sub_spm, e1@ptr, e2@ptr)
  new("spm", ptr=ptr)
}

div_spmspm = function(e1, e2)
{
  ptr = .Call(R_div_spm, e1@ptr, e2@ptr)
  new("spm", ptr=ptr)
}

pow_spmspm = function(e1, e2)
{
  ptr = .Call(R_pow_spm, e1@ptr, e2@ptr)
  new("spm", ptr=ptr)
}



binop = function(e1, e2, fun, spmfun)
{
  if ((!is.spm(e1) && !is.atomic(e1)) || (!is.spm(e2) && !is.atomic(e2)))
    stop("non-numeric argument to binary operator")
  
  if (is.spm(e1))
  {
    if (is.integer(e2))
      e2 = fl(e2)
    
    if (is.spm(e2))
      ret = spmfun(e1, e2)
    else
      ret = fun(dbl(e1), e2)
  }
  else
  {
    if (is.spm(e2))
    {
      if (is.integer(e1))
        ret = spmfun(fl(e1), e2)
      else
        ret = fun(e1, dbl(e2))
    }
    else
      ret = fun(e1, e2)
  }
  
  ret
}

add.spm = function(e1, e2)
{
  binop(e1, e2, `+`, add_spmspm)
}

mul.spm = function(e1, e2)
{
  binop(e1, e2, `*`, mul_spmspm)
}

sub.spm = function(e1, e2)
{
  binop(e1, e2, `-`, sub_spmspm)
}

div.spm = function(e1, e2)
{
  binop(e1, e2, `/`, div_spmspm)
}

pow.spm = function(e1, e2)
{
  binop(e1, e2, `^`, pow_spmspm)
}



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="LinAlg", e2="LinAlg"), add.spm)

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="LinAlg", e2="LinAlg"), mul.spm)

#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="LinAlg", e2="LinAlg"), sub.spm)

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="LinAlg", e2="LinAlg"), div.spm)

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="LinAlg", e2="LinAlg"), pow.spm)
