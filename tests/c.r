suppressPackageStartupMessages(library(float))
tol = 1e-6

x1 = 1:3
x2 = 6:7
x = c(pi, exp(1))
s1 = fl(x1)
s2 = fl(x2)

test = dbl(c(s1, s2))
truth = c(x1, x2)
stopifnot(all.equal(test, truth, tol=tol))

test = dbl(c(s1, x2))
stopifnot(all.equal(test, truth, tol=tol))

test = c(s1, x2, x)
truth = c(x1, x2, x)
stopifnot(all.equal(test, truth, tol=tol))
