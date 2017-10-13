suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6

x = crossprod(matrix(stats::rnorm(30), 10))
xs = fl(x)
y = 1:3
ys = fl(y)
z = cbind(y, rev(y))
zs = fl(z)


test = dbl(backsolve(xs, ys, upper.tri=FALSE))
truth = backsolve(x, y, upper.tri=FALSE)
stopifnot(all.equal(test, truth, tol=tol))

test = dbl(backsolve(xs, ys))
truth = backsolve(x, y)
stopifnot(all.equal(test, truth, tol=tol))

test = dbl(backsolve(xs, ys, k=2))
truth = backsolve(x, y, k=2)
stopifnot(all.equal(test, truth, tol=tol))

test = dbl(backsolve(xs, zs))
truth = backsolve(x, z)
stopifnot(all.equal(test, truth, tol=tol))

test = dbl(backsolve(xs, zs, k=2))
truth = backsolve(x, z, k=2)
stopifnot(all.equal(test, truth, tol=tol))
