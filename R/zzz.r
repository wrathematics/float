.onLoad <- function(libname, pkgname)
{
  .Call(R_init_NA, PACKAGE="spm")
  
  .Machine_float <<- .Call(R_machine_spm)
  
  invisible()
}
