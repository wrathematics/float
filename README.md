# spm

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/spm.png)](https://travis-ci.org/wrathematics/spm)
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


**spm** is a single precision matrix framework for R.

Type promotion always defaults to the higher precision.  So if a float matrix operates with an integer matrix, the integer matrix will be cast to a float first. Likewise if a float matrix operates with a double matrix, the float will be cast to a double first.  Similarly, any float matrix that is explicitly converted to a "regular" matrix will be stored in double precision.  Finally, vectors will be converted to numeric vectors (e.g. in `diag()` and `svd()`).



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
