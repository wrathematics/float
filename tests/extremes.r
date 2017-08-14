suppressPackageStartupMessages(library(spm))
set.seed(1234)
tol=1e-6

same = function(test, truth) stopifnot(all.equal(test, truth, tol=tol))

x1 = matrix(-4:5, 5)
s1 = fl(x1)

x2 = x1
x2[3, 1] = NA_integer_
x2[4, 2] = NA_integer_
s2 = fl(x2)

y = 1L
z = 1.0
s3 = flrunif(5)


### min
test = dbl(min(s1))
truth = min(x1)
same(test, truth)

test = dbl(min(s1, s3))
truth = min(x1, dbl(s3))
same(test, truth)

test = dbl(min(s1, y))
truth = min(x1, y)
same(test, truth)

# NA
test = dbl(sum(s2, na.rm=FALSE))
truth = sum(x2, na.rm=FALSE)
same(test, truth)

test = dbl(sum(s2, na.rm=TRUE))
truth = sum(x2, na.rm=TRUE)
same(test, truth)



### max
test = dbl(max(s1))
truth = max(x1)
same(test, truth)

test = dbl(max(s1, s3))
truth = max(x1, dbl(s3))
same(test, truth)

test = dbl(max(s1, y))
truth = max(x1, y)
same(test, truth)

# NA
test = dbl(sum(s2, na.rm=FALSE))
truth = sum(x2, na.rm=FALSE)
same(test, truth)

test = dbl(sum(s2, na.rm=TRUE))
truth = sum(x2, na.rm=TRUE)
same(test, truth)
