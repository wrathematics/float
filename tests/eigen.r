suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6

m = 10
n = 3

s = flrnorm(m, n)
cp_s = crossprod(s)
cp_d = dbl(cp_s)

test = eigen(cp_s, TRUE, TRUE)
truth = eigen(cp_d, TRUE, TRUE)
stopifnot(all.equal(dbl(test$values), truth$values, tol=tol))
stopifnot(identical(test$vectors, truth$vectors)) # both NULL

test = eigen(cp_s, TRUE, FALSE)
truth = eigen(cp_d, TRUE, FALSE)
stopifnot(all.equal(dbl(test$values), truth$values, tol=tol))
stopifnot(all.equal(abs(dbl(test$vectors)), abs(truth$vectors), tol=tol))
