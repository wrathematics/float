suppressPackageStartupMessages(library(float))

same = function(test, truth) stopifnot(all.equal(dbl(test), truth, tol=1e-6))

x = matrix(1:30, 10, 3)
s = fl(x)

test = sweep(s, 1, STATS=1L, FUN='+')
truth = sweep(x, 1, STATS=1L, FUN='+')
same(test, truth)

test = sweep(s, 1, STATS=1L, FUN='-')
truth = sweep(x, 1, STATS=1L, FUN='-')
same(test, truth)

test = sweep(s, 1, STATS=1L, FUN='*')
truth = sweep(x, 1, STATS=1L, FUN='*')
same(test, truth)

test = sweep(s, 1, STATS=1L, FUN='/')
truth = sweep(x, 1, STATS=1L, FUN='/')
same(test, truth)



test = sweep(s, 1, STATS=1:5, FUN='-')
truth = sweep(x, 1, STATS=1:5, FUN='-')
same(test, truth)



test = sweep(s, 2, STATS=1:3, FUN='-')
truth = sweep(x, 2, STATS=1:3, FUN='-')
same(test, truth)



test = sweep(s, 1, STATS=fl(pi), FUN='+')
truth = sweep(x, 1, STATS=pi, FUN='+')
same(test, truth)
