suppressPackageStartupMessages(library(float))
set.seed(1234)

testd = function(test, truth) all.equal(dbl(test$d), truth$d, tol=tol)
testu = function(test, truth) all.equal(dbl(abs(test$u)), abs(truth$u), tol=tol)
testv = function(test, truth) all.equal(dbl(abs(test$v)), abs(truth$v), tol=tol)
same = function(test, truth)
{
  stopifnot(testd(test, truth))
  stopifnot(ifelse(is.null(test$u), is.null(truth$u), testu(test, truth)))
  stopifnot(ifelse(is.null(test$v), is.null(truth$v), testv(test, truth)))
}

tester = function(s, x, ...)
{
  test = La.svd(s, ...)
  truth = La.svd(x, ...)
  same(test, truth)
}

tol = 1e-5



### m > n
m = 10
n = 3

s = flrnorm(m, n)
x = dbl(s)

tester(s, x, nu=0, nv=0)

tester(s, x, nv=0)
tester(s, x, nu=m, nv=0)
tester(s, x, nu=m-1, nv=0)
tester(s, x, nu=n, nv=0)
tester(s, x, nu=n-1, nv=0)

tester(s, x, nu=0)
tester(s, x, nu=0, nv=n)
tester(s, x, nu=0, nv=n-1)

tester(s, x, nu=m, nv=n)
tester(s, x)



### svd() driver
test = svd(s)
truth = svd(x)
same(test, truth)



### m < n
m = 3
n = 10

s = t(s)
x = t(x)

tester(s, x, nu=0, nv=0)

tester(s, x, nv=0)
tester(s, x, nu=m, nv=0)
tester(s, x, nu=m-1, nv=0)

tester(s, x, nu=0, nv=n)
tester(s, x, nu=0, nv=n-1)
tester(s, x, nu=0, nv=m)
tester(s, x, nu=0, nv=m-1)

tester(s, x, nu=m, nv=n)
tester(s, x)
