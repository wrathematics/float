.onLoad <- function(libname, pkgname)
{
  ret = .Call(R_init_NAf, PACKAGE="float")
  NA_float_ <<- float32(ret)
  
  ret = .Call(R_init_NaNf, PACKAGE="float")
  NaNf <<- float32(ret)
  
  .Machine_float <<- .Call(R_machine_spm)
  if(Sys.info()[["sysname"]] == "Darwin") {
    install_name_tool = "install_name_tool"
    which_install_name_tool = suppressWarnings(system2("which", install_name_tool, stdout = T))
    if(length(which_install_name_tool) == 0)
      stop(sprintf("you need to have '%s' installed", install_name_tool))
    
    path = system.file("libs", package = "float")
    path = file.path(path, "float.*")
    install_name_tool_args = sprintf('-id "@rpath%s" %s', path, path)
    # https://stackoverflow.com/a/44796734/1069256
    # run something like:
    # install_name_tool -id "@rpath/usr/local/lib/R/3.4/site-library/float/libs/float.*" /usr/local/lib/R/3.4/site-library/float/libs/float.*
    system2(install_name_tool, install_name_tool_args)
  }
  invisible()
}
