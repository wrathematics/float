# spm

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/spm.png)](https://travis-ci.org/wrathematics/spm)
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


**spm** is a single precision (aka float) matrix framework for R.  Base R has no single precision type.  Its "numeric" vectors/matrices are double precision (or possibly integer, but you know what I mean).  Floats have half the precision of double precision data, for a pretty obvious performance vs accuracy tradeoff.

A matrix of floats should use about half as much memory as a matrix of doubles, and your favorite matrix routines will generally compute about twice as fast on them as well.  However, the results will not be as accurate, and are much more prone to roundoff error/mass cancellation issues.  Statisticians have a habit of over-hyping the dangers of roundoff error in this author's opinion.  If your data is [well-conditioned](https://en.wikipedia.org/wiki/Condition_number), then using floats is "probably" fine for many applications.  

Type promotion always defaults to the higher precision.  So if a float matrix operates with an integer matrix, the integer matrix will be cast to a float first. Likewise if a float matrix operates with a double matrix, the float will be cast to a double first.  Similarly, any float matrix that is explicitly converted to a "regular" matrix will be stored in double precision.



## Installation

The package requires the single precision BLAS/LAPACK routines which are not included in the default `libRblas` and `libRlapack` shipped from CRAN.  If your BLAS/LAPACK libraries do not have what is needed, then they will be built (note that a fortran compiler is required in this case).  However, these can take a very long time to compile, and will have much worse performance than optimized libraries.  The topic of which BLAS/LAPACK to use and how to use them has been written about many times.  If this is the first you're hearing of it, I would recommend you use [Microsoft R Open](https://mran.microsoft.com/open/).

<!-- To install the R package, run:

```r
install.package("spm")
``` -->

The development version is maintained on GitHub, and can easily be installed by any of the packages that offer installations from GitHub:

```r
### Pick your preference
devtools::install_github("wrathematics/spm")
ghit::install_github("wrathematics/spm")
remotes::install_github("wrathematics/spm")
```



## Methods

The goal of the package is to recreate the matrix algebra facilities of the base package, but with floats.  So we do not include higher statistical methods (like `lm()` and `prcomp()`).

Is something missing?  Please [let me know](https://github.com/wrathematics/spm/issues).

### Basic utilities

| Method | Status |
|---|---|
| `[` | done |
| `c()` | done |
| `diag()` | done |
| `is.na()` | done |
| `is.spm()` | done |
| `min()` and `max()` | done |
| `na.omit()`, `na.exclude()` | done |
| `nrow()`, `ncol()`, `dim()` | done |
| `object.size()` | done |
| `print()` | done |
| `scale()` | Available for logical `center` and `scale` |
| `sweep()` | Available for `FUN`'s `"+"`, `"-"`, `"*"`, and `"/"`. Others impossible(?) | 
| `which.min()` and `which.max()` | done |

### Binary Operations

| Method | Status |
|---|---|
| `+` | done |
| `*` | done |
| `-` | done |
| `/` | done |
| `^` | done |
| `>` | done |
| `>=` | done |
| `==` | done |
| `<` | done |
| `<=` | done |

### Casters

| Method | Status |
|---|---|
| `mat2spm()` / `fl()` | done |
| `spm2mat()` / `dbl()` | done |

### Linear algebra

| Method | Status |
|---|---|
| `%*%` | done |
| `chol()` | done |
| `crossprod()` and `tcrossprod()` | done | 
| `eigen()` | only for symmetric inputs |
| `isSymmetric()` | done |
| `La.svd()` and `svd()` | done |
| `norm()` | done |
| `qr()`, `qr.Q()`, `qr.R()` | Mostly done; `qr.Q()` broken if `qr()` pivots |
| `solve()` | done | 
| `t()` | done |

### Math functions

| Method | Status |
|---|---|
| `abs()`, `sqrt()` | done |
| `ceiling()`, `floor()`, `trunc()`, `round()` | done |
| `exp()`, `exp1m()` | done |
| `gamma()`, `lgamma()` | done |
| `is.finite()`, `is.infinite()`, `is.nan()` | done |
| `log()`, `log10()`, `log2()` | done |
| `sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()` | done |
| `sinh()`, `cosh()`, `tanh()`, `asinh()`, `acosh()`, `atanh()` | done |

### Misc

| Method | Status |
|---|---|
| `.Machine_float` | float analogue of `.Machine`. everything you'd actually want is there |

### Sums and Means

| Method | Status |
|---|---|
| `colMeans()` | done |
| `colSums()` | done |
| `rowMeans()` | done |
| `rowSums()` | done |
| `sum()` | done |


### In progress and Future Plans

Version 0.1-0:

* finish/fix QR functions
* `rcond()`, and `kappa()`

Future roadmap:

* `cbind()` and `rbind()`
* `chol2inv()`
* A (low-level) reader, like `scan()`.
* An "in-place" (no copy on modify) API.

Maybe eventually:

* Support single complex.
* `fft()`



## Package Use

The memory consumption is roughly half when using floats:

```r
library(spm)

m = 10000
n = 2500

memuse::howbig(m, n)
## 190.735 MiB

x = matrix(rnorm(m*n), m, n)
object.size(x)
## 200000200 bytes

s = fl(x)
object.size(s)
## 100000672 bytes
```

And the runtime performance is roughly 2x better:

```r
library(rbenchmark)
cols <- cols <- c("test", "replications", "elapsed", "relative")
reps <- 5

benchmark(crossprod(x), crossprod(s), replications=reps, columns=cols)
##           test replications elapsed relative
## 2 crossprod(s)            5   3.185    1.000
## 1 crossprod(x)            5   7.163    2.249
```

However, the accuracy is better in the double precision version:

```r
cpx = crossprod(x)
cps = crossprod(s)
all.equal(cpx, dbl(cps))
## [1] "Mean relative difference: 3.478718e-07"
```

That difference is fairly small, but for some operations/data, the difference could be significantly larger due to roundoff error.



## A Note About Memory Consumption

Because we can not use "native" R objects to store our data (and must instead use an external pointer), the memory footprint for objects is actually quite large.  This cost is amortized quickly for reasonably large vectors/matrices.  But storing many very small float vectors/matrices can be surprisingly costly.

For example, consider the cost for a single float vector vs a double precision vector:

```r
object.size(fl(1))
## 676 bytes
object.size(double(1))
## 48 bytes
```

However once we get to 158 elements, the storage is identical:

```r
object.size(fl(1:158))
## 1304 bytes
object.size(double(158))
## 1304 bytes
```

And for vectors/matrices with many elements, the size of the double precision data is roughly twice that of the float data:

```r
object.size(fl(1:10000))
## 40672 bytes
object.size(double(10000))
## 80040 bytes
```

The above analysis assumes that your `float` and `double` values are conforming to the [IEEE-754 standard](https://en.wikipedia.org/wiki/IEEE_754) (which is required to build this package).  It specifies that a `float` requires 4 bytes, and a `double` requires 8.  The size of an `int` is actually system dependent, but is probably 4 bytes.  This means that for most, a float matrix should always be larger than a similarly sized integer matrix, because the overhead for our float matrix is simply larger.  However, for objects with many elements, the sizes will be roughly equal:

```r
object.size(fl(1:10000))
## 40672 bytes
object.size(1:10000)
## 40040 bytes
```
