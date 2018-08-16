# linux: "linux"
# mac: "darwin"
# windows:
# freebsd: "freebsd"
get_os <- function()
{
  os = tolower(Sys.info()["sysname"])
  names(os) = NULL
  
  os
}



ldflags_string = function(static=FALSE)
{
  install_path = "libs"
  
  os = get_os()
  dynamic_link = (os == "linux" || os == "freebsd" || os == "darwin")  &&  !isTRUE(static)
  
  if (nchar(.Platform$r_arch) > 0)
    path = file.path(install_path, .Platform$r_arch)
  else
    path = install_path
  
  float_libs_dir_rel = system.file(path, package="float")
  float_libs_dir = tools::file_path_as_absolute(float_libs_dir_rel)
  
  if (dynamic_link)
  {
    if (os == "darwin")
      flags = paste0("-L", float_libs_dir, " ", float_libs_dir, "/float.so -Wl,-rpath ", float_libs_dir)
    else
      flags = paste0("-L", float_libs_dir, " -l:float.so -Wl,-rpath=", float_libs_dir)
  }
  else
    flags = paste0(float_libs_dir, "/libfloat.a")
  
  flags
}



ldflags = function(static=FALSE)
{
  flags = ldflags_string(static=static)
  
  cat(flags)
  invisible()
}
