suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6

x = crossprod(matrix(stats::rnorm(30), 10))
xs = fl(x)

test = dbl(chol(xs))
stopifnot(all.equal(test, chol(x), tol=tol))
