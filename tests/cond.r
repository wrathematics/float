suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-4
m = 10
n = 3

x = matrix(stats::rnorm(m*n), m, n)
s = fl(x)

type = "O"
test = dbl(rcond(s, type))
truth = rcond(x, type)
stopifnot(all.equal(test, truth, tol=tol))

type = "I"
test = dbl(rcond(s, type))
truth = rcond(qr.R(qr(x, LAPACK=TRUE)), type)
stopifnot(all.equal(test, truth, tol=tol))



cp = crossprod(x)
cp_s = fl(cp)

type = "O"
test = dbl(rcond(cp_s, type))
truth = rcond(cp, type)
stopifnot(all.equal(test, truth, tol=tol))

type = "I"
test = dbl(rcond(cp_s, type))
truth = rcond(cp, type)
stopifnot(all.equal(test, truth, tol=tol))
