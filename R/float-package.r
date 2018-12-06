#' 32-Bit Floats
#' 
#' @description
#' R comes with a suite of utilities for linear algebra with "numeric"
#' (double precision) vectors/matrices. However, sometimes single precision (or
#' less!) is more than enough for a particular task.  This package extends R's
#' linear algebra facilities to include 32-bit float (single precision) data.
#' Float vectors/matrices have half the precision of their "numeric"-type
#' counterparts but are generally faster to numerically operate on, for a
#' performance vs accuracy trade-off.  The internal representation is an S4
#' class, which allows us to keep the syntax identical to that of base R's.
#' Interaction between floats and base types for binary operators is generally
#' possible; in these cases, type promotion always defaults to the higher
#' precision.  The package ships with copies of the single precision 'BLAS' and
#' 'LAPACK', which are automatically built in the event they are not available
#' on the system.
#' 
#' @importFrom utils capture.output str
#' @import methods
#' 
#' @docType package
#' @name float-package
#' @author Drew Schmidt
#' @keywords package
NULL
