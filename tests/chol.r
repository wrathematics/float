suppressPackageStartupMessages(library(spm))
set.seed(1234)

tol = 1e-6

x = crossprod(matrix(rnorm(30), 10))
xs = mat2spm(x)

test = spm2mat(chol(xs))
stopifnot(all.equal(test, chol(x), tol=tol))

