.onLoad <- function(libname, pkgname)
{
  .Call(R_init_NA, PACKAGE="spm")
  invisible()
}
