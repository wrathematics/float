library(stats)
library(float, quietly=TRUE)
library(rbenchmark)

reps = 5
cols <- c("test", "replications", "elapsed", "relative")

m = 7500
n = 500
x = matrix(rnorm(m*n), m, n)
s = fl(x)

prcomp_spm = function(x)
{
  p = svd(scale(x, TRUE, FALSE), nu=0)
  p$d = p$d / max(1, sqrt(nrow(x) - 1))
  names(p) = c("sdev", "rotation")
  
  p
}



benchmark(prcomp_spm(x), prcomp_spm(s), prcomp(x, retx=FALSE), replications=reps, columns=cols)
