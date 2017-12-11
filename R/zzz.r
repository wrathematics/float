.onLoad <- function(libname, pkgname)
{
  ret = .Call(R_init_NAf, PACKAGE="float")
  NA_float_ <<- float32(ret)
  
  ret = .Call(R_init_NaNf, PACKAGE="float")
  NaNf <<- float32(ret)
  
  .Machine_float <<- .Call(R_machine_spm)
  
  invisible()
}
