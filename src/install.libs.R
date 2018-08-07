### Modified from Rserve/src/install.libs.R
### For libs
files <- c("float.so", "float.so.dSYM", "float.dylib", "float.dll",
           "symbols.rds", "libfloat.a")
files <- files[file.exists(files)]
if(length(files) > 0){
  libsarch <- if (nzchar(R_ARCH)) paste("libs", R_ARCH, sep='') else "libs"
  dest <- file.path(R_PACKAGE_DIR, libsarch)
  dir.create(dest, recursive = TRUE, showWarnings = FALSE)
  file.copy(files, dest, overwrite = TRUE, recursive = TRUE)
}
