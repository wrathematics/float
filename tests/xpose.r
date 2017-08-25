suppressPackageStartupMessages(library(float))

x = matrix(1:30, 10)
y = matrix(1:10, 2, 10)
z = matrix(1:5, 5, 3)

xs = fl(x)
ys = fl(y)
zs = fl(z)


test = dbl(t(xs))
stopifnot(all.equal(test, t(x)))

test = dbl(t(ys))
stopifnot(all.equal(test, t(y)))

test = dbl(t(zs))
stopifnot(all.equal(test, t(z)))
