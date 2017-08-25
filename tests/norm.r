suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6
m = 10
n = 3

x = matrix(stats::rnorm(m*n), m, n)
s = fl(x)

type = "O"
test = dbl(norm(s, type))
truth = norm(x, type)
stopifnot(all.equal(test, truth, tol=tol))

type = "I"
test = dbl(norm(s, type))
truth = norm(x, type)
stopifnot(all.equal(test, truth, tol=tol))

type = "F"
test = dbl(norm(s, type))
truth = norm(x, type)
stopifnot(all.equal(test, truth, tol=tol))

type = "M"
test = dbl(norm(s, type))
truth = norm(x, type)
stopifnot(all.equal(test, truth, tol=tol))

type = "2"
test = dbl(norm(s, type))
truth = norm(x, type)
stopifnot(all.equal(test, truth, tol=tol))
