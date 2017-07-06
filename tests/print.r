suppressPackageStartupMessages(library(spm))

m = 10L
n = 3L

x = matrix(1:(m*n), m, n)
xs = mat2spm(x)

stopifnot(identical(nrow(x), m))
stopifnot(identical(ncol(x), n))
stopifnot(identical(dim(x), c(m, n)))

p = paste(capture.output(print(xs)), collapse="\n")
truth = "# An spm (single precision matrix): 10x3
      [,1] [,2] [,3]
 [1,]    1   11   21
 [2,]    2   12   22
 [3,]    3   13   23
 [4,]    4   14   24
 [5,]    5   15   25
 [6,]    6   16   26
 [7,]    7   17   27
 [8,]    8   18   28
 [9,]    9   19   29
[10,]   10   20   30"

stopifnot(identical(p, truth))
