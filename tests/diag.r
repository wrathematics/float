suppressPackageStartupMessages(library(float))

### Diag taker
x = matrix(1:30, 10)
y = matrix(1:10, 10, 2)
z = matrix(1:5, 5, 3)

xs = fl(x)
ys = fl(y)
zs = fl(z)


test = dbl(diag(xs))
stopifnot(all.equal(test, diag(x)))

test = dbl(diag(ys))
stopifnot(all.equal(test, diag(y)))

test = dbl(diag(zs))
stopifnot(all.equal(test, diag(z)))



### Diag maker
tester = function(x, s)
{
  truth = diag(x)
  test = dbl(diag(s))
  stopifnot(all.equal(test, truth))
  
  truth = diag(x, 3, 2)
  test = dbl(diag(s, 3, 2))
  stopifnot(all.equal(test, truth))
  
  truth = diag(x, 5, 5)
  test = dbl(diag(s, 5, 5))
  stopifnot(all.equal(test, truth))
}


x = 1:4
s = fl(x)
tester(x, s)

x = c(3, 7)
s = fl(x)
tester(x, s)
