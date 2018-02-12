ldflags = function()
{
  if (.Platform$OS.type != "windows")
  {
    so.path = tools::file_path_as_absolute(system.file("libs", package = "float"))
    flags = file.path(so.path, "float.so")
  }
  else
  {
    path = file.path("libs", .Platform$r_arch)
    dll.path = tools::file_path_as_absolute(system.file(path, package = "float"))
    flags = file.path(dll.path, "float.dll")
  }
  
  cat("-L", flags, sep = "")
}
