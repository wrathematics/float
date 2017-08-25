suppressPackageStartupMessages(library(float))
set.seed(1234)
tol = 1e-6

same = function(test, truth) stopifnot(all.equal(test, truth, tol=tol))

x1 = matrix(stats::rnorm(30), 10)
x2 = matrix(stats::rnorm(30), 10)
x3 = matrix(1:30, 10)

s1 = fl(x1)
s2 = fl(x2)



### Addition
test = dbl(s1 + s2)
truth = x1 + x2
same(test, truth)
test = s1 + x2
same(test, truth)
test = x2 + s1
same(test, truth)

test = dbl(s1 + x3)
truth = x1 + x3
same(test, truth)
test = dbl(x3 + s1)
same(test, truth)

test = dbl(s1 + 1L)
truth = x1 + 1
same(test, truth)
test = s1 + 1.0
same(test, truth)



### Multiplication
test = dbl(s1 * s2)
truth = x1 * x2
same(test, truth)
test = s1 * x2
same(test, truth)
test = x2 * s1
same(test, truth)

test = dbl(s1 * x3)
truth = x1 * x3
same(test, truth)
test = dbl(x3 * s1)
same(test, truth)

test = dbl(s1 * 1L)
truth = x1 * 1L
same(test, truth)
test = s1 * 1.0
same(test, truth)



### Subtraction
test = dbl(s1 - s2)
truth = x1 - x2
same(test, truth)
test = s1 - x2
same(test, truth)

truth = x2 - x1
test = x2 - s1
same(test, truth)

test = dbl(s1 - x3)
truth = x1 - x3
same(test, truth)

truth = x3 - x1
test = dbl(x3 - s1)
same(test, truth)

test = dbl(s1 - 1L)
truth = x1 - 1L
same(test, truth)
test = s1 - 1.0
same(test, truth)



### Division
test = dbl(s1 / s2)
truth = x1 / x2
same(test, truth)
test = s1 / x2
same(test, truth)

truth = x2 / x1
test = x2 / s1
same(test, truth)

test = dbl(s1 / x3)
truth = x1 / x3
same(test, truth)

truth = x3 / x1
test = dbl(x3 / s1)
same(test, truth)

test = dbl(s1 / 1L)
truth = x1 / 1L
same(test, truth)
test = s1 / 1.0
same(test, truth)



### Power
test = dbl(s1 ^ s2)
truth = x1 ^ x2
same(test, truth)
test = s1 ^ x2
same(test, truth)

truth = x2 ^ x1
test = x2 ^ s1
same(test, truth)

test = dbl(s1 ^ x3)
truth = x1 ^ x3
same(test, truth)

truth = x3 ^ x1
test = dbl(x3 ^ s1)
same(test, truth)

test = dbl(s1 ^ 1L)
truth = x1 ^ 1L
same(test, truth)
test = s1 ^ 1.0
same(test, truth)
