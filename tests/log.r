library(spm)
set.seed(1234)

same = function(test, truth, tol=1e-6) stopifnot(all.equal(dbl(test), truth, tol=tol))


x = runif(30, 1, 20)
s = fl(x)

test = exp(s)
truth = exp(x)
same(test, truth)

test = expm1(s)
truth = expm1(x)
same(test, truth)

test = log(s)
truth = log(x)
same(test, truth)

test = log(s, 3)
truth = log(x, 3)
same(test, truth)

test = log10(s)
truth = log10(x)
same(test, truth)

test = log2(s)
truth = log2(x)
same(test, truth)

