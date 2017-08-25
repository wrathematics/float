suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6

x = crossprod(matrix(stats::rnorm(30), 10))
xs = fl(x)
y = 1:3
ys = fl(y)

solve_xy = solve(x, y)



test = dbl(solve(xs))
stopifnot(all.equal(test, solve(x), tol=tol))

test = dbl(solve(xs, ys))
stopifnot(all.equal(test, solve_xy, tol=tol))

test = dbl(solve(xs, y))
stopifnot(all.equal(test, solve_xy, tol=tol))

test = solve(xs, as.double(y))
stopifnot(all.equal(test, solve_xy, tol=tol))
