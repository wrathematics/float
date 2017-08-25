suppressPackageStartupMessages(library(float))

x = matrix(1:30, 10)
y = matrix(1:9, 3)

x_y = x %*% y

xs = fl(x)
ys = fl(y)

test = dbl(xs %*% ys)
stopifnot(all.equal(test, x_y))

test = dbl(xs %*% y)
stopifnot(all.equal(test, x_y))

test = dbl(x %*% ys)
stopifnot(all.equal(test, x_y))



storage.mode(x) = "double"
storage.mode(y) = "double"

test = xs %*% y
stopifnot(all.equal(test, x_y))

test = x %*% ys
stopifnot(all.equal(test, x_y))
