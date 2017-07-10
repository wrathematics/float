suppressPackageStartupMessages(library(spm))

x = matrix(1:30, 10)
y = matrix(1:10, 10, 2)
z = matrix(1:5, 5, 3)

xs = mat2spm(x)
ys = mat2spm(y)
zs = mat2spm(z)


test = spm2mat(diag(xs))
stopifnot(all.equal(test, diag(x)))

test = spm2mat(diag(ys))
stopifnot(all.equal(test, diag(y)))

test = spm2mat(diag(zs))
stopifnot(all.equal(test, diag(z)))
