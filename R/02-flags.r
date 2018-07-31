# freebsd: "freebsd"
# linux: "linux"
# mac: "darwin"
# windows: "windows"
get_os <- function()
{
  os = tolower(Sys.info()["sysname"])
  names(os) = NULL
  
  os
}



ldflags_string = function()
{
  os = get_os()
  install_path = "libs"
  
  if (nchar(.Platform$r_arch) > 0)
    path = file.path(install_path, .Platform$r_arch)
  else
    path = install_path
  
  float_libs_dir_rel = system.file(path, package="float")
  float_libs_dir = tools::file_path_as_absolute(float_libs_dir_rel)
  
  # FIXME we use -Wl,-rpath for linux, which is sufficient for CRAN but not necessarily safe; needs more checks
  if (os == "linux" || os == "freebsd")
    flags = paste0("-L", float_libs_dir, " -l:float.so -Wl,-rpath=", float_libs_dir)
  else
    flags = paste0(float_libs_dir, "/float.*")
  
  
  flags
}



ldflags = function()
{
  flags = ldflags_string()
  
  cat(flags)
  invisible()
}
