library(spm)
library(rbenchmark)

reps = 5
cols <- c("test", "replications", "elapsed", "relative")

m = 7500
n = 500
x = matrix(stats::rnorm(m*n), m, n)
s = fl(x)

cov_spm = function(x)
{
  s = scale(x, TRUE, FALSE)
  crossprod(s) / max(1, nrow(x)-1)
}

cor_spm = function(x)
{
  s = scale(x, TRUE, TRUE)
  crossprod(s) / max(1, nrow(x)-1)
}



benchmark(cov_spm(x), cov_spm(s), cov(x), replications=reps, columns=cols)
cat("\n")
benchmark(cor_spm(x), cor_spm(s), cor(x), replications=reps, columns=cols)
