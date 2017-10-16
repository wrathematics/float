suppressPackageStartupMessages(library(float))
set.seed(1234)

tester = function(s, x, fun)
{
  test = dbl(fun(s, na.rm=TRUE))
  truth = fun(x, na.rm=TRUE)
  stopifnot(all.equal(test, truth, tol=tol))
  
  test = dbl(fun(s, na.rm=FALSE))
  truth = fun(x, na.rm=FALSE)
  stopifnot(all.equal(test, truth, tol=tol))
}

tol = 1e-6
m = 5
n = 3

x1 = matrix(stats::rnorm(m*n), m, n)
x2 = x1
x2[1, 1] = NA_real_
x2[3, 2] = NaN

s1 = fl(x1)
s2 = fl(x2)



tester(s1, x1, colSums)
tester(s2, x2, colSums)

tester(s1, x1, rowSums)
tester(s2, x2, rowSums)

tester(s1, x1, colMeans)
tester(s2, x2, colMeans)

tester(s1, x1, rowMeans)
tester(s2, x2, rowMeans)
