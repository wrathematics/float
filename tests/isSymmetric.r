suppressPackageStartupMessages(library(float))

x = matrix(1:30, 10)
y = matrix(1:10, 10, 2)
z = crossprod(x)
w = z
w[1, 2] = -123456

xs = fl(x)
ys = fl(y)
zs = fl(z)
ws = fl(w)


test = isSymmetric(xs)
truth = isSymmetric(x)
stopifnot(identical(test, truth))

test = isSymmetric(ys)
truth = isSymmetric(y)
stopifnot(identical(test, truth))

test = isSymmetric(zs)
truth = isSymmetric(z)
stopifnot(identical(test, truth))

test = isSymmetric(ws)
truth = isSymmetric(w)
stopifnot(identical(test, truth))
