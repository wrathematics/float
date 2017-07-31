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
   
  ptr = .Call(R_flrunif_spm, m, n, as.double(min), as.double(max), isavec)
  new("spm", ptr=ptr)
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
   
  ptr = .Call(R_flrnorm_spm, m, n, as.double(mean), as.double(sd), isavec)
  new("spm", ptr=ptr)
}
