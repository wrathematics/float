suppressPackageStartupMessages(library(float))

x = matrix(1:30, 10)
y = matrix(1:10, 10, 2)
z = matrix(1:5, 5, 3)

xs = fl(x)
ys = fl(y)
zs = fl(z)

cpxy = crossprod(x, y)
tcpxz = tcrossprod(x, z)


test = dbl(crossprod(xs))
stopifnot(all.equal(test, crossprod(x)))

test = dbl(crossprod(xs, ys))
stopifnot(all.equal(test, cpxy))

test = crossprod(x, ys)
stopifnot(all.equal(test, cpxy))

test = crossprod(xs, y)
stopifnot(all.equal(test, cpxy))



test = dbl(tcrossprod(xs))
stopifnot(all.equal(test, tcrossprod(x)))

test = dbl(tcrossprod(xs, zs))
stopifnot(all.equal(test, tcpxz))

test = tcrossprod(x, zs)
stopifnot(all.equal(test, tcpxz))

test = tcrossprod(xs, z)
stopifnot(all.equal(test, tcpxz))
