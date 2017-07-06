suppressPackageStartupMessages(library(spm))

x = matrix(1:30, 10)
y = matrix(1:10, 2, 10)
z = matrix(1:5, 5, 3)

xs = mat2spm(x)
ys = mat2spm(y)
zs = mat2spm(z)


test = spm2mat(t(xs))
stopifnot(all.equal(test, t(x)))

test = spm2mat(t(ys))
stopifnot(all.equal(test, t(y)))

test = spm2mat(t(zs))
stopifnot(all.equal(test, t(z)))
