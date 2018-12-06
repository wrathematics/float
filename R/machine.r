#' Machine_float
#' 
#' Numerical characteristics of the machine for floats. Contains analogues of
#' much of the double precision details of \code{.Machine}.
#' 
#' Values are taken directly from \code{float.h}.
#' 
#' @format 
#' A list containing:
#' \describe{
#'   \item \code{float.eps} epsilon
#'   \item \code{float.xmin} smallest non-zero float
#'   \item \code{float.xmax} largest non-inf float
#'   \item \code{float.base} radix
#'   \item \code{float.digits} the number of bits for the sign+significand
#'   \item \code{float.exponent} number of bits for the exponent
#'   \item \code{float.min.exp} "largest negative" (smallest) integer for the
#'       exponent that generates a normalized floating-point number
#'   \item \code{float.max.exp} largest integer for the
#'       exponent that generates a normalized floating-point number
#' }
#' 
#' @docType data
"Machine_float"
