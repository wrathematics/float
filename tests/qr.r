suppressPackageStartupMessages(library(float))
set.seed(1234)

tol = 1e-6

cmp = function(qr_x, qr_xs)
{
  test = dbl(qr.R(qr_xs))
  truth = qr.R(qr_x)
  stopifnot(all.equal(test, truth, tol=tol))
  
  test = dbl(qr.Q(qr_xs))
  truth = qr.Q(qr_x)
  stopifnot(all.equal(test, truth, tol=tol))

  test = dbl(qr.R(qr_xs, complete=TRUE))
  truth = qr.R(qr_x, complete=TRUE)
  stopifnot(all.equal(test, truth, tol=tol))
  
  test = dbl(qr.Q(qr_xs, complete=TRUE))
  truth = qr.Q(qr_x, complete=TRUE)
  stopifnot(all.equal(test, truth, tol=tol))
}


# m > n
x = matrix(stats::rnorm(30), 10)
xs = fl(x)
qr_x = qr(x, LAPACK=TRUE)
qr_xs = qr(xs)

stopifnot(identical(qr_xs$rank, 3L))
cmp(qr_x, qr_xs)



# NOTE: m < n and rank degenerate cases not well-defined
