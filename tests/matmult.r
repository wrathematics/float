suppressPackageStartupMessages(library(float))

x = matrix(1:30, 10)
y = matrix(1:9, 3)

x_y = x %*% y

xs = mat2spm(x)
ys = mat2spm(y)

test = spm2mat(xs %*% ys)
stopifnot(all.equal(test, x_y))

test = spm2mat(xs %*% y)
stopifnot(all.equal(test, x_y))

test = spm2mat(x %*% ys)
stopifnot(all.equal(test, x_y))



storage.mode(x) = "double"
storage.mode(y) = "double"

test = xs %*% y
stopifnot(all.equal(test, x_y))

test = x %*% ys
stopifnot(all.equal(test, x_y))
