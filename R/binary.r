# apply a binary operation with appropriate type promotion
binop = function(e1, e2, fun, floatfun)
{
  if ((!is.float(e1) && !is.atomic(e1)) || (!is.float(e2) && !is.atomic(e2)))
    stop("non-numeric argument to binary operator")
  
  if (is.float(e1))
  {
    if (is.integer(e2))
      e2 = fl(e2)
    
    if (is.float(e2))
      ret = floatfun(e1, e2)
    else
      ret = fun(dbl(e1), e2)
  }
  else
  {
    if (is.float(e2))
    {
      if (is.integer(e1))
        ret = floatfun(fl(e1), e2)
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
#' library(float)
#' 
#' s1 = flrunif(5, 5)
#' s2 = flrunif(5, 5)
#' x = matrix(1:25, 5)
#' 
#' s1 + s2 # float
#' 
#' typeof(x) # integer
#' x + s2 # float
#' 
#' storage.mode(x) = "double"
#' x + s2 # double
#' 
#' @name arithmetic
#' @rdname arithmetic
NULL



add_floatfloat = function(e1, e2)
{
  ret = .Call(R_add_spm, DATA(e1), DATA(e2))
  float32(ret)
}

mul_floatfloat = function(e1, e2)
{
  ret = .Call(R_mul_spm, DATA(e1), DATA(e2))
  float32(ret)
}

sub_floatfloat = function(e1, e2)
{
  ret = .Call(R_sub_spm, DATA(e1), DATA(e2))
  float32(ret)
}

div_floatfloat = function(e1, e2)
{
  ret = .Call(R_div_spm, DATA(e1), DATA(e2))
  float32(ret)
}

pow_floatfloat = function(e1, e2)
{
  ret = .Call(R_pow_spm, DATA(e1), DATA(e2))
  float32(ret)
}



add.float = function(e1, e2)
{
  binop(e1, e2, `+`, add_floatfloat)
}

mul.float = function(e1, e2)
{
  binop(e1, e2, `*`, mul_floatfloat)
}

sub.float = function(e1, e2)
{
  binop(e1, e2, `-`, sub_floatfloat)
}

div.float = function(e1, e2)
{
  binop(e1, e2, `/`, div_floatfloat)
}

pow.float = function(e1, e2)
{
  binop(e1, e2, `^`, pow_floatfloat)
}



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="float32", e2="float32"), add.float)

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="float32", e2="float32"), mul.float)

#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="float32", e2="float32"), sub.float)

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="float32", e2="float32"), div.float)

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="float32", e2="float32"), pow.float)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="float32", e2="BaseLinAlg"), add.float)

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="float32", e2="BaseLinAlg"), mul.float)

#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="float32", e2="BaseLinAlg"), sub.float)

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="float32", e2="BaseLinAlg"), div.float)

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="float32", e2="BaseLinAlg"), pow.float)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="BaseLinAlg", e2="float32"), add.float)

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="BaseLinAlg", e2="float32"), mul.float)

#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="BaseLinAlg", e2="float32"), sub.float)

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="BaseLinAlg", e2="float32"), div.float)

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="BaseLinAlg", e2="float32"), pow.float)



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
#' library(float)
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



lt_floatfloat = function(e1, e2)
{
  .Call(R_lt_spm, DATA(e1), DATA(e2))
}

le_floatfloat = function(e1, e2)
{
  .Call(R_le_spm, DATA(e1), DATA(e2))
}

eq_floatfloat = function(e1, e2)
{
  .Call(R_eq_spm, DATA(e1), DATA(e2))
}

gt_floatfloat = function(e1, e2)
{
  .Call(R_gt_spm, DATA(e1), DATA(e2))
}

ge_floatfloat = function(e1, e2)
{
  .Call(R_ge_spm, DATA(e1), DATA(e2))
}



lt.float = function(e1, e2)
{
  binop(e1, e2, `<`, lt_floatfloat)
}

le.float = function(e1, e2)
{
  binop(e1, e2, `<=`, le_floatfloat)
}

eq.float = function(e1, e2)
{
  binop(e1, e2, `==`, eq_floatfloat)
}

gt.float = function(e1, e2)
{
  binop(e1, e2, `>`, gt_floatfloat)
}

ge.float = function(e1, e2)
{
  binop(e1, e2, `>=`, ge_floatfloat)
}



#' @rdname arithmetic
#' @export
setMethod("<", signature(e1="float32", e2="float32"), lt.float)

#' @rdname arithmetic
#' @export
setMethod("<=", signature(e1="float32", e2="float32"), le.float)

#' @rdname arithmetic
#' @export
setMethod("==", signature(e1="float32", e2="float32"), eq.float)

#' @rdname arithmetic
#' @export
setMethod(">", signature(e1="float32", e2="float32"), gt.float)

#' @rdname arithmetic
#' @export
setMethod(">=", signature(e1="float32", e2="float32"), ge.float)



#' @rdname arithmetic
#' @export
setMethod("<", signature(e1="float32", e2="BaseLinAlg"), lt.float)

#' @rdname arithmetic
#' @export
setMethod("<=", signature(e1="float32", e2="BaseLinAlg"), le.float)

#' @rdname arithmetic
#' @export
setMethod("==", signature(e1="float32", e2="BaseLinAlg"), eq.float)

#' @rdname arithmetic
#' @export
setMethod(">", signature(e1="float32", e2="BaseLinAlg"), gt.float)

#' @rdname arithmetic
#' @export
setMethod(">=", signature(e1="float32", e2="BaseLinAlg"), ge.float)



#' @rdname arithmetic
#' @export
setMethod("<", signature(e1="BaseLinAlg", e2="float32"), lt.float)

#' @rdname arithmetic
#' @export
setMethod("<=", signature(e1="BaseLinAlg", e2="float32"), le.float)

#' @rdname arithmetic
#' @export
setMethod("==", signature(e1="BaseLinAlg", e2="float32"), eq.float)

#' @rdname arithmetic
#' @export
setMethod(">", signature(e1="BaseLinAlg", e2="float32"), gt.float)

#' @rdname arithmetic
#' @export
setMethod(">=", signature(e1="BaseLinAlg", e2="float32"), ge.float)
