# float

* **Version:** 0.2-0
* **Status:** [![Linux Build Status via Travis-CI](https://travis-ci.org/wrathematics/float.png)](https://travis-ci.org/wrathematics/float) [![Windows build status via AppVeyor](https://ci.appveyor.com/api/projects/status/github/wrathematics/float?branch=master&svg=true)](https://ci.appveyor.com/project/wrathematics/float/branch/master)
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt
* **Project home**: https://github.com/wrathematics/float
* **Bug reports**: https://github.com/wrathematics/float/issues


**float** is a single precision (aka float) matrix framework for R.  Base R has no single precision type.  Its "numeric" vectors/matrices are double precision (or possibly integer, but you know what I mean).  Floats have half the precision of double precision data, for a pretty obvious performance vs accuracy tradeoff.

A matrix of floats should use about half as much memory as a matrix of doubles, and your favorite matrix routines will generally compute about twice as fast on them as well.  However, the results will not be as accurate, and are much more prone to roundoff error/mass cancellation issues.  Statisticians have a habit of over-hyping the dangers of roundoff error in this author's opinion.  If your data is [well-conditioned](https://en.wikipedia.org/wiki/Condition_number), then using floats is "probably" fine for many applications.  

⚠️ **WARNING** ⚠️ type promotion always defaults to the higher precision.  So if a float matrix operates with an integer matrix, the integer matrix will be cast to a float first. Likewise if a float matrix operates with a double matrix, the float will be cast to a double first.  Similarly, any float matrix that is explicitly converted to a "regular" matrix will be stored in double precision.



## Installation

The package requires the single precision BLAS/LAPACK routines which are not included in the default `libRblas` and `libRlapack` shipped from CRAN.  If your BLAS/LAPACK libraries do not have what is needed, then they will be built (note that a fortran compiler is required in this case).  However, these can take a very long time to compile, and will have much worse performance than optimized libraries.  The topic of which BLAS/LAPACK to use and how to use them has been written about many times.  If this is the first you're hearing of it, I would recommend you use [Microsoft R Open](https://mran.microsoft.com/open/).

To install the R package, run:

```r
install.package("float")
```

The development version is maintained on GitHub, and can easily be installed by any of the packages that offer installations from GitHub:

```r
remotes::install_github("wrathematics/float")
```

### Windows
If you are installing on Windows and wish to get the best performance, then you will need to install from source after editing some files.  After installing high-performance BLAS and LAPACK libraries, delete the text `$(LAPACK_OBJS)` from line in `src/Makevars.win` beginning with `OBJECTS = `.  You will also need to add the appropriate link line.  This will ensure that on building, the package links with your high-performance libraries instead of compiling the reference versions.  This is especially important for 32-bit Windows where the internal LAPACK and BLAS libraries are built without compiler optimization because of a compiler bug.

Also, if you are using Windows on big endian hardware (I'm not even sure if this is possible), then you will need to change the 0 in `src/windows/endianness.h` to a 1. Failure to do so will cause very bizarre things to happen with the NA handlers.



## Creating, Casting, and Type

Before we get to the main usage of the package and its methods, 

* To cast TO a float (convert an existing numeric vector/matrix), use `as.float()` (or its shorthand `fl()`).
* To cast FROM a float, use `as.double()` or `as.integer()` (or their shorthands, `dbl()` and `int()`).
* To pre-allocate a float vector of 0's (like `integer(5)`), use `float()`.
* To construct a float32 object (developes only; see the vignette), use `float32()`.

R has a generic number type "numeric" which encompasses integers and doubles. The function `is.numeric()` will `FALSE` for float vectors/matries. Similarly, `as.numeric()` will return the data cast as double.



## Methods

The goal of the package is to recreate the matrix algebra facilities of the base package, but with floats.  So we do not include higher statistical methods (like `lm()` and `prcomp()`).

Is something missing?  Please [let me know](https://github.com/wrathematics/float/issues).

### Basic utilities

| Method | Status |
|---|---|
| `[` | done |
| `c()` | done |
| `cbind()` and `rbind()` | done |
| `diag()` | done |
| `is.na()` | done |
| `is.float()` | done |
| `min()` and `max()` | done |
| `na.omit()`, `na.exclude()` | done |
| `nrow()`, `ncol()`, `dim()` | done |
| `object.size()` | done |
| `print()` | done |
| `rep()` | done |
| `scale()` | Available for logical `center` and `scale` |
| `str()` | done |
| `sweep()` | Available for `FUN`'s `"+"`, `"-"`, `"*"`, and `"/"`. Others impossible(?) | 
| `typeof()` and `storage.mode()` | No `storage.mode<-` method. |
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

### Casters and Converters

| Method | Status |
|---|---|
| `dbl()` | done |
| `int()` | done |
| `fl()` | done |
| `as.vector()` and `as.matrix()` | done |

### Linear algebra

| Method | Status |
|---|---|
| `%*%` | done |
| `backsolve()` and `forwardsolve()` | done |
| `chol()`, `chol2inv()` | done |
| `crossprod()` and `tcrossprod()` | done | 
| `eigen()` | only for symmetric inputs |
| `isSymmetric()` | done |
| `La.svd()` and `svd()` | done |
| `norm()` | done |
| `qr()`, `qr.Q()`, `qr.R()` | done |
| `rcond()` | done |
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



## Package Use

Memory consumption is roughly half when using floats:

```r
library(float)

m = 10000
n = 2500

memuse::howbig(m, n)
## 190.735 MiB

x = matrix(rnorm(m*n), m, n)
object.size(x)
## 200000200 bytes

s = fl(x)
object.size(s)
## 100000784 bytes
```

And the runtime performance is (generally) roughly 2x better:

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

For this particular example, the difference is fairly small; but for some operations/data, the difference could be significantly larger due to roundoff error.



## A Note About Memory Consumption

Because of the use of S4 for the nice syntax, there is some memory overhead which is noticeable for small vectors/matrices.  This cost is amortized quickly for reasonably large vectors/matrices.  But storing many very small float vectors/matrices can be surprisingly costly.

For example, consider the cost for a single float vector vs a double precision vector:

```r
object.size(fl(1))
## 632 bytes
object.size(double(1))
## 48 bytes
```

However once we get to 147 elements, the storage is identical:

```r
object.size(fl(1:147))
## 1216 bytes
object.size(double(147))
## 1216 bytes
```

And for vectors/matrices with many elements, the size of the double precision data is roughly twice that of the float data:

```r
object.size(fl(1:10000))
## 40624 bytes
object.size(double(10000))
## 80040 bytes
```

The above analysis assumes that your `float` and `double` values are conforming to the [IEEE-754 standard](https://en.wikipedia.org/wiki/IEEE_754) (which is required to build this package).  It specifies that a `float` requires 4 bytes, and a `double` requires 8.  The size of an `int` is actually system dependent, but is probably 4 bytes.  This means that for most, a float matrix should always be larger than a similarly sized integer matrix, because the overhead for our float matrix is simply larger.  However, for objects with many elements, the sizes will be roughly equal:

```r
object.size(fl(1:10000))
## 40624 bytes
object.size(1:10000)
## 40040 bytes
```



## Q&A

#### Why would I want to do arithmetic in single precision?

It's (generally) twice as fast and uses half the RAM compared to double precision. For a some data analysis tasks, that's more important than having (roughly) twice as many decimal digits.

#### Why does `floatmat + 1` produce a numeric (double) matrix but `floatmat + 1L` produce a float matrix?

Type promotion always defaults to the highest type available. If you want the arithmetic to be carried out in single precision, cast the `1` with `fl(1)` first.

#### Doesn't that make R's type system even more of a mess?

Yes.

#### How would I create my own methods?

If you can formulate the method in terms of existing functionality from the **float** package, then you're good.  If not, you will likely have to write your own C/C++ code.  See the *For Developers* section of the package vignette.
