suppressPackageStartupMessages(library(spm))

x = matrix(1:30, 10)
y = matrix(1:10, 10, 2)
z = matrix(1:5, 5, 3)

xs = mat2spm(x)
ys = mat2spm(y)
zs = mat2spm(z)

cpxy = crossprod(x, y)
tcpxz = tcrossprod(x, z)


test = spm2mat(crossprod(xs))
stopifnot(all.equal(test, crossprod(x)))

test = spm2mat(crossprod(xs, ys))
stopifnot(all.equal(test, cpxy))

test = crossprod(x, ys)
stopifnot(all.equal(test, cpxy))

test = crossprod(xs, y)
stopifnot(all.equal(test, cpxy))



test = spm2mat(tcrossprod(xs))
stopifnot(all.equal(test, tcrossprod(x)))

test = spm2mat(tcrossprod(xs, zs))
stopifnot(all.equal(test, tcpxz))

test = tcrossprod(x, zs)
stopifnot(all.equal(test, tcpxz))

test = tcrossprod(xs, z)
stopifnot(all.equal(test, tcpxz))
