suppressPackageStartupMessages(library(float))
set.seed(1234)
tol=1e-6

same = function(test, truth) stopifnot(all.equal(test, truth, tol=tol))

x1 = matrix(-4:5, 5)
s1 = fl(x1)
y = 1L
z = 1.0
s2 = flrunif(5)


test = dbl(sum(s1))
truth = sum(x1)
same(test, truth)

test = dbl(sum(s1, s2))
truth = sum(x1, dbl(s2))
same(test, truth)

test = dbl(sum(s1, y))
truth = sum(x1, y)
same(test, truth)



x2 = x1
x2[3, 1] = NA_integer_
x2[4, 2] = NA_integer_
s2 = fl(x2)

test = dbl(sum(s2, na.rm=FALSE))
truth = sum(x2, na.rm=FALSE)
same(test, truth)

test = dbl(sum(s2, na.rm=TRUE))
truth = sum(x2, na.rm=TRUE)
same(test, truth)
