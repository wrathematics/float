suppressPackageStartupMessages(library(float))

### Diag taker
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



### Diag maker
tester = function(x, s)
{
  truth = diag(x)
  test = spm2mat(diag(s))
  stopifnot(all.equal(test, truth))
  
  truth = diag(x, 3, 2)
  test = spm2mat(diag(s, 3, 2))
  stopifnot(all.equal(test, truth))
  
  truth = diag(x, 5, 5)
  test = spm2mat(diag(s, 5, 5))
  stopifnot(all.equal(test, truth))
}


x = 1:4
s = fl(x)
tester(x, s)

x = c(3, 7)
s = fl(x)
tester(x, s)
