suppressPackageStartupMessages(library(float))

same = function(test, truth) stopifnot(all.equal(dbl(test), truth, tol=1e-6, check.attributes=FALSE))

m = 10
n = 3

x = matrix(stats::rnorm(m*n), m, n)
s = fl(x)

test = scale(s, TRUE, TRUE)
truth = scale(x, TRUE, TRUE)
same(test, truth)

test = scale(s, TRUE, FALSE)
truth = scale(x, TRUE, FALSE)
same(test, truth)

test = scale(s, FALSE, TRUE)
truth = scale(x, FALSE, TRUE)
same(test, truth)

test = scale(s, FALSE, FALSE)
truth = scale(x, FALSE, FALSE)
same(test, truth)
