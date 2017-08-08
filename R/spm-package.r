#' Single Precision Matrices
#' 
#' @description
#' R comes with a suite of utilities for linear algebra with "numeric"
#' (double precision) vectors/matrices. However, sometimes single precision
#' (or less!) is more than enough for a particular task.  This package extends
#' R's linear algebra facilities to include single precision (float) data.
#' Float vectors/matrices have half the precision of their "numeric"-type
#' counterparts, for a performance vs accuracy tradeoff.  The internal
#' representation is an S4 class, which allows us to keep the syntax identical
#' to that of base R's.  Interaction between base types for binary operators
#' is generally possible.  In these cases, type promotion always defaults to
#' the higher precision.  The package ships with copies of the single precision
#' BLAS and LAPACK, which are automatically built in the event they are needed.
#' 
#' @importFrom utils capture.output
#' @import methods
#' 
#' @useDynLib spm R_mat2spm R_spm2mat R_crossprod_spm R_crossprod_spmspm
#'   R_tcrossprod_spm R_tcrossprod_spmspm R_matmult_spm R_xpose_spm
#'   R_diag_spm R_diagmat_spm R_chol_spm R_solve_spm R_solve_spmspm
#'   R_bracket_spm R_nrow_spm R_ncol_spm R_dim_spm R_isSymmetric_spm R_svd_spm
#'   R_isavec_spm R_qr_spm R_qrQ_spm R_qrR_spm R_numbytes_spm
#'   R_flrunif_spm R_flrnorm_spm R_exp_spm R_expm1_spm R_log_spm R_log10_spm
#'   R_log2_spm R_sin_spm R_cos_spm R_tan_spm R_asin_spm R_acos_spm R_atan_spm
#'   R_sinh_spm R_cosh_spm R_tanh_spm R_asinh_spm R_acosh_spm R_atanh_spm
#'   R_abs_spm R_sqrt_spm R_isfinite_spm R_isinfinite_spm R_isnan_spm
#'   R_gamma_spm R_lgamma_spm R_isna_spm R_naomit_spm R_add_spm R_mul_spm
#' 
#' @docType package
#' @name spm-package
#' @author Drew Schmidt
#' @keywords package
NULL
