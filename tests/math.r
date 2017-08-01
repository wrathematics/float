library(spm)
set.seed(1234)

same = function(fun, s, x, tol=1e-6, ...) stopifnot(all.equal(dbl(fun(s, ...)), fun(x, ...), tol=tol))

x = runif(30, 0.1, 1)
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
