library(stats)
library(float, quietly=TRUE)
library(rbenchmark)
set.seed(1234)

reps = 5
cols <- c("test", "replications", "elapsed", "relative")

m = 7500
n = 500
x = matrix(rnorm(m*n), m, n)
y = rnorm(m)
s = fl(x)
t = fl(y)

### m >= n only
lmfit_spm <- function(x, y)
{
  QR = qr(x, LAPACK=TRUE)
  Q = qr.Q(QR)
  R = qr.R(QR)
  coef = solve(R, crossprod(Q,  y))
  
  resid <- y - x %*% coef
  eff <- crossprod(Q, y)
  
  
  list(coefficients=coef, residuals=resid, effects=eff)
}



benchmark(lmfit_spm(x, y), lmfit_spm(s, t), lm.fit(x, y), replications=reps, columns=cols)
