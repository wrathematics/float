# spm

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/spm.png)](https://travis-ci.org/wrathematics/spm)
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


**spm** is a single precision matrix framework for R.  The package is nearly feature complete with base R's matrix operations, which is probably good enough for most everyone.

Type promotion always defaults to the higher precision.  So if a float matrix operates with an integer matrix, the integer matrix will be cast to a float first. Likewise if a float matrix operates with a double matrix, the float will be cast to a double first.  Similarly, any float matrix that is explicitly converted to a "regular" matrix will be stored in double precision.



## Installation

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



## Package Use

Example:

```r
suppressPackageStartupMessages(library(spm))

m = 10000
n = 2500
memuse::howbig(10000, 2500)
## 190.735 MiB

x = matrix(rnorm(m*n), m, n)

t1 = system.time(crossprod(x))
t1
##  user  system elapsed 
## 5.076   0.672   1.508 

t2 = system.time({
  xs = fl(x)
  cp = crossprod(xs)
  dbl(cp)
})
t2
##  user  system elapsed 
## 2.316   0.668   0.811 

t1[3] / t2[3]
## elapsed 
## 1.859433 
```

So it's almost 2 times faster to do the crossproduct in this case with floats, even counting the cost of conversion both ways. Which makes sense.
