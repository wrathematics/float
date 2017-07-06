suppressPackageStartupMessages(library(spm))
set.seed(1234)

tol = 1e-6

x = crossprod(matrix(rnorm(30), 10))
xs = mat2spm(x)
y = 1:3
ys = mat2spm(y)

solve_xy = solve(x, y)



test = spm2mat(solve(xs))
stopifnot(all.equal(test, solve(x), tol=tol))

test = spm2mat(solve(xs, ys))
stopifnot(all.equal(test, solve_xy, tol=tol))

test = spm2mat(solve(xs, y))
stopifnot(all.equal(test, solve_xy, tol=tol))

test = solve(xs, as.double(y))
stopifnot(all.equal(test, solve_xy, tol=tol))
