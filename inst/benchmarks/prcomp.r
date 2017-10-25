library(stats)
library(float, quietly=TRUE)
library(rbenchmark)
set.seed(1234)

reps = 5
cols <- c("test", "replications", "elapsed", "relative")

m = 7500
n = 500
x = matrix(rnorm(m*n), m, n)
s = fl(x)

pca_spm = function(x)
{
  p = svd(scale(x, TRUE, FALSE), nu=0)
  p$d = p$d / max(1, sqrt(nrow(x) - 1))
  names(p) = c("sdev", "rotation")
  
  p
}

pca = function(x) prcomp(x, retx=FALSE)

benchmark(pca_spm(x), pca_spm(s), pca(x), replications=reps, columns=cols)
