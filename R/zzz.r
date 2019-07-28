#' @useDynLib float R_init_NAf R_machine_spm R_init_NaNf

.onLoad <- function(libname, pkgname)
{
  NA_float_ = float32(.Call(R_init_NAf, PACKAGE="float"))
  # NaNf = float32(.Call(R_init_NaNf, PACKAGE="float"))
  # .Machine_float = .Call(R_machine_spm)
  
  ### Disable the following since R-3.6.0
  if (Sys.info()[["sysname"]] == "Darwin" && getRversion() < "3.6.0")
  {
    install_name_tool = "install_name_tool"
    which_install_name_tool = suppressWarnings(system2("which", install_name_tool, stdout = T))
    if(length(which_install_name_tool) == 0)
      stop(sprintf("you need to have '%s' installed", install_name_tool))
    
    path.libs = system.file("libs", package = "float")
    files = c("float.so", "float.dylib")
    for(i.file in files){
      path = file.path(path.libs, i.file)
      if(file.exists(path)){
        install_name_tool_args = sprintf('-id "@rpath%s" %s', path, path)
        # https://stackoverflow.com/a/44796734/1069256
        # run something like:
        # install_name_tool -id "@rpath/usr/local/lib/R/3.4/site-library/float/libs/float.*" /usr/local/lib/R/3.4/site-library/float/libs/float.*
        system2(install_name_tool, install_name_tool_args)
      }
    }
  }
  invisible()
}
