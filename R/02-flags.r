ldflags = function()
{
  if (.Platform$OS.type != "windows")
  {
    so.path = tools::file_path_as_absolute(system.file("libs", package="float"))
    flags = paste0(so.path, "/float.so")
  }
  else
  {
    # path = paste0("libs/", .Platform$r_arch)
    # dll.path = tools::file_path_as_absolute(system.file(path, package="float"))
    # flags = paste0(dll.path, "/float.dll")
    
    path = paste0("libs/", .Platform$r_arch)
    dll.path = tools::file_path_as_absolute(system.file(path, package="float"))
    dll.path <- normalizePath(dll.path)
    dll.path <- utils::shortPathName(dll.path)
    dll.path <- gsub("\\\\", "/", dll.path)
    flags = paste0(dll.path, "/float.dll")
  }
  
  cat(flags)
}
