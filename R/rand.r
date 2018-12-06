#' Generators
#' 
#' Random float vector/matrix generators. \code{flrunif()} produces uniform
#' random values. \code{flrnorm()} produces random normal values.
#' \code{flrand()} will accept an arbitrary generator. See the details section
#' for more information.
#' 
#' @details
#' For \code{flrunif()} and \code{flrnorm()}, the data is produced without a
#' double precision copy.  That is, it is not (computationally) equivalent to
#' \code{fl(matrix(runif(...)))}, though the operations are conceptually the
#' same.  For these, To produce a vector instead of a matrix, leave argument
#' \code{n} blank. Setting \code{n=1} will produce an mx1 matrix.
#' 
#' For \code{flrand()}, the data is generated in double precision in 4KiB
#' batches and copied over to a pre-allocated vector.  This will be slower than
#' generating all of the data up front and copying it, although it uses far less
#' memory most of the time.  So you can think of \code{flrunif()} and
#' \code{flrnorm()} as highly optimized versions of \code{flrand()} for uniform
#' and normal generators specifically.
#' 
#' @param m,n
#' The dimensions of the matrix/vector. \code{m} must be specified.  If \code{n}
#' is not, then the return is a vector.
#' @param min,max
#' Minimum and maximum values for the uniform generator.
#' @param mean,sd
#' Mean and standard deviation values for the normal generator.
#' @param generator
#' A generating function, such as \code{rnorm}, or even something custom
#' defined.
#' @param ...
#' Additional arguments passed to the generator. For example, if \code{runif} is
#' passed as \code{generator}, then you might additionally pass \code{max=10}.
#' 
#' @examples
#' library(float)
#' 
#' flrunif(10) # length 10 vector
#' flrunif(10, 1) # 10x1 matrix
#' flrunif(10, min=10, max=20)
#' 
#' flrand(runif, 10) # conceptually the same as flrunif(10)
#' 
#' mygen = function(n) sample(1:5, n, replace=TRUE)
#' flrand(mygen, 30)
#' 
#' @useDynLib float R_flrunif_spm R_flrnorm_spm R_flrand_spm
#' @name rand
#' @rdname rand
NULL



#' @rdname rand
#' @export
flrunif = function(m, n, min=0, max=1)
{
  m = as.integer(m)
  if (missing(n))
  {
    n = 1L
    isavec = TRUE
  }
  else
  {
    n = as.integer(n)
    isavec = FALSE
  }
  
  if (m < 0)
    stop("invalid 'm' value (< 0)")
  if (n < 0)
    stop("invalid 'n' value (< 0)")
  
  ret = .Call(R_flrunif_spm, m, n, as.double(min), as.double(max), isavec)
  float32(ret)
}



#' @rdname rand
#' @export
flrnorm = function(m, n, mean=0, sd=1)
{
  m = as.integer(m)
  if (missing(n))
  {
    n = 1L
    isavec = TRUE
  }
  else
  {
    n = as.integer(n)
    isavec = FALSE
  }
   
  if (m < 0)
    stop("invalid 'm' value (< 0)")
  if (n < 0)
    stop("invalid 'n' value (< 0)")
  
  ret = .Call(R_flrnorm_spm, m, n, as.double(mean), as.double(sd), isavec)
  float32(ret)
}



flrand_batch = function(start, data, generator, len, ...)
{
  gen = generator(len, ...)
  if (!is.integer(gen) && !is.double(gen))
    storage.mode(gen) = "double"
  
  .Call(R_flrand_spm, data, start, len, gen)
  start + len
}

#' @rdname rand
#' @export
flrand = function(generator, m, n, ...)
{
  m = as.integer(m)
  if (missing(n))
  {
    n = 1L
    isavec = TRUE
  }
  else
  {
    n = as.integer(n)
    isavec = FALSE
  }
  
  n = m*n
  
  MAX = 512L # 4k chunks of doubles
  fullruns = as.integer(n/MAX)
  rem = as.integer(n - fullruns*MAX)
  
  data = integer(n)
  start = 1L
  for (i in seq_len(fullruns))
    start = flrand_batch(start, data, generator, MAX, ...)
  
  if (rem)
    start = flrand_batch(start, data, generator, rem, ...)
  
  float32(data)
}
