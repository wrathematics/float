library(float)

x = c(1, 2, -1, -2, 0, 100, -100, 0)
s = fl(x)

test = all.equal(sign(x), sign(s))
stopifnot(isTRUE(test))
