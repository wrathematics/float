suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6

x = crossprod(matrix(stats::rnorm(30), 10))
xs = fl(x)


test = dbl(chol2inv(chol(xs)))
truth = chol2inv(chol(x))
stopifnot(all.equal(test, truth, tol=tol))
