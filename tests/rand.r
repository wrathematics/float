suppressPackageStartupMessages(library(float))
set.seed(1234)

sd = stats::sd

### uniform
s = flrunif(500)
x = dbl(s)
stopifnot(min(x) >= 0)
stopifnot(max(x) <= 1)

s = flrunif(500, min=50, max=60)
x = dbl(s)
stopifnot(min(x) >= 50)
stopifnot(max(x) <= 60)

m = 10L
n = 5L
s = flrunif(m, n)
stopifnot(identical(dim(s), c(m, n))) 


### normal
s = flrnorm(5000)
x = dbl(s)
stopifnot(abs(mean(x)-0) < 1e-1)
stopifnot(abs(sd(x)-1) < 1e-1)


s = flrnorm(5000, mean=10, sd=5)
x = dbl(s)
stopifnot(abs(mean(x)-10) < 1e-1)
stopifnot(abs(sd(x)-5) < 1e-1)

m = 5L
n = 10L
s = flrnorm(m, n)
stopifnot(identical(dim(s), c(m, n))) 
