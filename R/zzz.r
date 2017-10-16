.onLoad <- function(libname, pkgname)
{
  ret = .Call(R_init_NA, PACKAGE="float")
  NA_float_ <<- new("float32", Data=ret)
  
  .Machine_float <<- .Call(R_machine_spm)
  
  invisible()
}
