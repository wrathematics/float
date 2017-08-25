suppressPackageStartupMessages(library(float))
set.seed(1234)


x1 = c(1, NaN, Inf, -Inf, 2, NA_real_)
s1 = fl(x1)

x2 = matrix(1:30, 10)
x2[c(1, 3, 5, 7), 3] = NA
x2[2, 1] = NA
s2 = fl(x2)

stopifnot(all.equal(is.na(s1), is.na(x1)))
stopifnot(all.equal(is.na(s2), is.na(x2)))



stopifnot(all.equal(dbl(na.omit(s1)), na.omit(x1), check.attributes=FALSE))
stopifnot(all.equal(dbl(na.omit(s2)), na.omit(x2), check.attributes=FALSE))

stopifnot(all.equal(dbl(na.omit(na.omit(s1))), na.omit(na.omit(x1)), check.attributes=FALSE))
stopifnot(all.equal(dbl(na.omit(na.omit(s2))), na.omit(na.omit(x2)), check.attributes=FALSE))
