.onLoad <- function(libname, pkgname)
{
  .Call(R_init_NA, PACKAGE="float")
  
  .Machine_float <<- .Call(R_machine_spm)
  
  invisible()
}
