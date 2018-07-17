suppressPackageStartupMessages(library(float))

tol = 1e-6

x = matrix(1:6, 3, 2)
s = fl(x)

test = dbl(rep(s, 5))
truth = rep(x, 5)
stopifnot(all.equal(test, truth, tol=tol))
