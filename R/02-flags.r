ldflags=function(arch='')
{
  if (.Platform$OS.type != "windows")
  {
    file.path = paste("lib/", arch, sep="")
    ld.path = tools::file_path_as_absolute(system.file(file.path, package="float"))
    flags = paste(ld.path, "/libslapack.a", sep="")
  }
  else
  {
    file.path = paste("lib/", .Platform$r_arch, sep="")
    ld.path = tools::file_path_as_absolute(system.file(file.path, package="float"))
    flags = paste("\"", ld.path, "/libslapack.a", "\"", sep="")
  }
  
  cat(flags)
}
