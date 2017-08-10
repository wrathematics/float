# apply a binary operation with appropriate type promotion
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



# -----------------------------------------------------------------------------
# arithmetic
# -----------------------------------------------------------------------------

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
setMethod("+", signature(e1="spm", e2="spm"), add.spm)

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="spm", e2="spm"), mul.spm)

#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="spm", e2="spm"), sub.spm)

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="spm", e2="spm"), div.spm)

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="spm", e2="spm"), pow.spm)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="spm", e2="BaseLinAlg"), add.spm)

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="spm", e2="BaseLinAlg"), mul.spm)

#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="spm", e2="BaseLinAlg"), sub.spm)

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="spm", e2="BaseLinAlg"), div.spm)

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="spm", e2="BaseLinAlg"), pow.spm)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="BaseLinAlg", e2="spm"), add.spm)

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="BaseLinAlg", e2="spm"), mul.spm)

#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="BaseLinAlg", e2="spm"), sub.spm)

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="BaseLinAlg", e2="spm"), div.spm)

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="BaseLinAlg", e2="spm"), pow.spm)



# -----------------------------------------------------------------------------
# Comparisons
# -----------------------------------------------------------------------------

#' comparison
#' 
#' Binary comparison operators for numeric/float matrices.
#' 
#' @param e1,e2
#' Numeric/float vectors/matrices.
#' 
#' @return
#' A vector/matrix of logicals.
#' 
#' @examples
#' \dontrun{
#' library(spm)
#' s = flrunif(5, 5)
#' x = matrix(1:25, 5)
#' 
#' s > x
#' s <= 0
#' }
#' 
#' @name comparison
#' @rdname comparison
NULL



lt_spmspm = function(e1, e2)
{
  .Call(R_lt_spm, e1@ptr, e2@ptr)
}

le_spmspm = function(e1, e2)
{
  .Call(R_le_spm, e1@ptr, e2@ptr)
}

eq_spmspm = function(e1, e2)
{
  .Call(R_eq_spm, e1@ptr, e2@ptr)
}

gt_spmspm = function(e1, e2)
{
  .Call(R_gt_spm, e1@ptr, e2@ptr)
}

ge_spmspm = function(e1, e2)
{
  .Call(R_ge_spm, e1@ptr, e2@ptr)
}



lt.spm = function(e1, e2)
{
  binop(e1, e2, `<`, lt_spmspm)
}

le.spm = function(e1, e2)
{
  binop(e1, e2, `<=`, le_spmspm)
}

eq.spm = function(e1, e2)
{
  binop(e1, e2, `==`, eq_spmspm)
}

gt.spm = function(e1, e2)
{
  binop(e1, e2, `>`, gt_spmspm)
}

ge.spm = function(e1, e2)
{
  binop(e1, e2, `>=`, ge_spmspm)
}



#' @rdname arithmetic
#' @export
setMethod("<", signature(e1="spm", e2="spm"), lt.spm)

#' @rdname arithmetic
#' @export
setMethod("<=", signature(e1="spm", e2="spm"), le.spm)

#' @rdname arithmetic
#' @export
setMethod("==", signature(e1="spm", e2="spm"), eq.spm)

#' @rdname arithmetic
#' @export
setMethod(">", signature(e1="spm", e2="spm"), gt.spm)

#' @rdname arithmetic
#' @export
setMethod(">=", signature(e1="spm", e2="spm"), ge.spm)



#' @rdname arithmetic
#' @export
setMethod("<", signature(e1="spm", e2="BaseLinAlg"), lt.spm)

#' @rdname arithmetic
#' @export
setMethod("<=", signature(e1="spm", e2="BaseLinAlg"), le.spm)

#' @rdname arithmetic
#' @export
setMethod("==", signature(e1="spm", e2="BaseLinAlg"), eq.spm)

#' @rdname arithmetic
#' @export
setMethod(">", signature(e1="spm", e2="BaseLinAlg"), gt.spm)

#' @rdname arithmetic
#' @export
setMethod(">=", signature(e1="spm", e2="BaseLinAlg"), ge.spm)



#' @rdname arithmetic
#' @export
setMethod("<", signature(e1="BaseLinAlg", e2="spm"), lt.spm)

#' @rdname arithmetic
#' @export
setMethod("<=", signature(e1="BaseLinAlg", e2="spm"), le.spm)

#' @rdname arithmetic
#' @export
setMethod("==", signature(e1="BaseLinAlg", e2="spm"), eq.spm)

#' @rdname arithmetic
#' @export
setMethod(">", signature(e1="BaseLinAlg", e2="spm"), gt.spm)

#' @rdname arithmetic
#' @export
setMethod(">=", signature(e1="BaseLinAlg", e2="spm"), ge.spm)
