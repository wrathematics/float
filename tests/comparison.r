suppressPackageStartupMessages(library(float))
set.seed(1234)

same = function(test, truth) stopifnot(identical(test, truth))
tester = function(s, x, test)
{
  same(s >  test, x > test)
  same(s >= test, x >= test)
  same(s == test, x == test)
  same(s <  test, x < test)
  same(s <= test, x <= test)
  
  same(test >  s, test > x)
  same(test >= s, test >= x)
  same(test == s, test == x)
  same(test <  s, test < x)
  same(test <= s, test <= x)
}

x = matrix(-4:5, 5)
s = fl(x)

tester(s, x, 0L)
tester(s, x, 0.0)
tester(s, x, fl(0))
tester(s, x, s)
tester(s, x, x)
