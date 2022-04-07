# linux: "linux"
# mac: "darwin"
# windows: "windows"
# freebsd: "freebsd"
get_os <- function()
{
  os = tolower(Sys.info()["sysname"])
  names(os) = NULL
  
  os
}



blas_ldflags_string = function()
{
  if (get_os() == "windows")
  {
    maj = as.numeric(version$major)
    min = floor(as.numeric(version$minor))
    if (maj < 4 || min <= 1)
      ""
    else
      "-lblas"
  }
  else
    blas_ldflags_nix() # defined by configure in R/02-libflags.r
}

lapack_ldflags_string = function()
{
  if (get_os() == "windows")
  {
    maj = as.numeric(version$major)
    min = floor(as.numeric(version$minor))
    if (maj < 4 || min <= 1)
      ""
    else
      "-llapack"
  }
  else
    lapack_ldflags_nix() # defined by configure in R/02-libflags.r
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
    {
      libfiles = c("float.so", "float.dylib")
      libfile = NULL
      for (libfile_test in libfiles)
      {
        if (file.exists(paste0(float_libs_dir, "/", libfile_test)))
        {
          libfile = libfile_test
          break
        }
      }
      if (is.null(libfile))
        stop(paste("unable to dynamically link: can't find any of:", paste(libfiles, collapse=", ")))
      
      flags = paste0("-L", float_libs_dir, " ", float_libs_dir, "/", libfile, " -Wl,-rpath ", float_libs_dir)
    }
    else
      flags = paste0("-L", float_libs_dir, " -l:float.so -Wl,-rpath=", float_libs_dir)
  }
  else
    flags = paste0(float_libs_dir, "/libfloat.a")
  
  flags
}

ldflags = function(static=FALSE)
{
  linalg_flags = paste(lapack_ldflags_string(), blas_ldflags_string())
  float_flags = ldflags_string(static=static)
  flags = paste(float_flags, linalg_flags)
  
  cat(flags)
  invisible()
}



cppflags_string = function()
{
  install_path = "include"
  
  if (nchar(.Platform$r_arch) > 0)
    path = file.path(install_path, .Platform$r_arch)
  else
    path = install_path
  
  float_include_dir_rel = system.file(path, package="float")
  float_include_dir = tools::file_path_as_absolute(float_include_dir_rel)
  
  flags = paste0("-I", float_include_dir)
  flags
}

cppflags = function()
{
  flags = cppflags_string()
  
  cat(flags)
  invisible()
}
