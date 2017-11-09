suppressPackageStartupMessages(library(float))
tol = 1e-6

x = matrix(1:10, 5)
s = fl(x)

test = dbl(rbind(s, s))
truth = rbind(x, x)
stopifnot(all.equal(test, truth))

test = dbl(rbind(s, 1L))
truth = rbind(x, 1L)
stopifnot(all.equal(test, truth))

test = rbind(s, 1.0)
truth = rbind(x, 1.0)
stopifnot(all.equal(test, truth))



test = dbl(cbind(s, s))
truth = cbind(x, x)
stopifnot(all.equal(test, truth))

test = dbl(cbind(s, 1L))
truth = cbind(x, 1L)
stopifnot(all.equal(test, truth))

test = cbind(s, 1.0)
truth = cbind(x, 1.0)
stopifnot(all.equal(test, truth))
