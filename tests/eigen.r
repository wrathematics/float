suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6

m = 10
n = 3

s = flrnorm(m, n)
cp_s = crossprod(s)
cp_d = dbl(cp_s)

test = eigen(cp_s, symmetric=TRUE, only.values=TRUE)
truth = eigen(cp_d, symmetric=TRUE, only.values=TRUE)
stopifnot(all.equal(dbl(test$values), truth$values, tol=tol))
stopifnot(identical(test$vectors, truth$vectors)) # both NULL

test = eigen(cp_s, symmetric=TRUE, only.values=FALSE)
truth = eigen(cp_d, symmetric=TRUE, only.values=FALSE)
stopifnot(all.equal(dbl(test$values), truth$values, tol=tol))
stopifnot(all.equal(abs(dbl(test$vectors)), abs(truth$vectors), tol=tol))
