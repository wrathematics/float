suppressPackageStartupMessages(library(float))
set.seed(1234)

same = function(fun, s, x, tol=1e-6, ...) stopifnot(all.equal(dbl(fun(s, ...)), fun(x, ...), tol=tol))

x = stats::runif(30, 0.1, 1)
s = fl(x)

# -----------------------------------------------------------------------------
# logs
# -----------------------------------------------------------------------------

same(exp, s, x)
same(expm1, s, x)
same(log, s, x)
same(log, s, x, base=3)
same(log10, s, x)
same(log2, s, x)

# -----------------------------------------------------------------------------
# trig
# -----------------------------------------------------------------------------

same(sin, s, x)
same(cos, s, x)
same(tan, s, x)
same(asin, s, x)
same(acos, s, x)
same(atan, s, x)

# -----------------------------------------------------------------------------
# hyperbolic
# -----------------------------------------------------------------------------

x2 = 1:30
s2 = fl(x2)

same(sinh, s, x)
same(cosh, s, x)
same(tanh, s, x)
same(asinh, s, x)
same(acosh, s2, x2)
same(atanh, s, x)

# -----------------------------------------------------------------------------
# misc
# -----------------------------------------------------------------------------

same(abs, s, x)
same(sqrt, s, x)

# -----------------------------------------------------------------------------
# special
# -----------------------------------------------------------------------------

same(gamma, s, x)
same(lgamma, s, x)

# -----------------------------------------------------------------------------
# mathis
# -----------------------------------------------------------------------------

x3 = c(1, NaN, Inf, -Inf, 2, NA_real_)
s3 = fl(x3)

stopifnot(identical(is.finite(s3), is.finite(x3)))
stopifnot(identical(is.infinite(s3), is.infinite(x3)))
stopifnot(identical(is.nan(s3), is.nan(x3)))

# -----------------------------------------------------------------------------
# mathis
# -----------------------------------------------------------------------------


pis = fl(pi)

same(ceiling, pis, pi)
same(floor, pis, pi)
same(trunc, pis, pi)

same(round, pis, pi)
same(round, pis, pi, digits=1)
same(round, pis, pi, digits=2)
same(round, pis, pi, digits=3)
same(round, pis, pi, digits=-1)
