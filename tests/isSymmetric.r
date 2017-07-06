suppressPackageStartupMessages(library(spm))

x = matrix(1:30, 10)
y = matrix(1:10, 10, 2)
z = crossprod(x)
w = z
w[1, 2] = -123456

xs = mat2spm(x)
ys = mat2spm(y)
zs = mat2spm(z)
ws = mat2spm(w)


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
