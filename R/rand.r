#' Generators
#' 
#' Random float vector/matrix generators. \code{flrunif()} produces uniform
#' random values. \code{flrnorm()} produces random normal values.
#' 
#' @details
#' The data is produced without a double precision copy.  That is, it is not
#' (computationally) equivalent to \code{fl(matrix(runif(...)))}, though the
#' operations are conceptually the same.
#' 
#' To produce a vector instead of a matrix, leave argument \code{n} blank.
#' Setting \code{n=1} will produce an mx1 matrix.
#' 
#' @param m,n
#' The dimensions of the matrix/vector. \code{m} must be specified.  If \code{n}
#' is not, then the return is a vector.
#' @param min,max
#' Minimum and maximum values for the uniform generator.
#' @param mean,sd
#' Mean and standard deviation values for the normal generator.
#' 
#' @examples
#' \dontrun{
#' library(float)
#' 
#' flrunif(10) # length 10 vector
#' flrunif(10, 1) # 10x1 matrix
#' flrunif(10, min=10, max=20)
#' }
#' 
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
  new("float32", Data=ret)
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
  new("float32", Data=ret)
}
