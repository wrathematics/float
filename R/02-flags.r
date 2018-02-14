ldflags = function()
{
  if (.Platform$OS.type != "windows")
  {
    flags = tools::file_path_as_absolute(system.file("libs", package = "float"))
  }
  else
  {
    path = file.path("libs", .Platform$r_arch)
    flags = tools::file_path_as_absolute(system.file(path, package = "float"))
  }
  cat("-L", flags,  sep = "")
}
