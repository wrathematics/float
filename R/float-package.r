#' 32-Bit Floats
#' 
#' @description
#' R comes with a suite of utilities for linear algebra with "numeric"
#' (double precision) vectors/matrices. However, sometimes single precision (or
#' less!) is more than enough for a particular task.  This package extends R's
#' linear algebra facilities to include 32-bit float (single precision) data.
#' Float vectors/matrices have half the precision of their "numeric"-type but
#' are generally faster to numerically operate on, for a performance vs
#' accuracy trade-off.  The internal representation is an S4 class, which
#' allows us to keep the syntax identical to that of base R's.  Interaction
#' between floats and base types for binary operators is generally possible; in
#' these cases, type promotion always defaults to the higher precision.  The
#' package ships with copies of the single precision 'BLAS' and 'LAPACK', which
#' are automatically built in the event they are not available on the system.
#' 
#' @importFrom utils capture.output str
#' @import methods
#' 
#' @useDynLib float R_mat2spm R_spm2mat R_init_NA R_machine_spm R_crossprod_spm
#'   R_crossprod_spmspm R_tcrossprod_spm R_tcrossprod_spmspm R_add_spm R_mul_spm
#'   R_sub_spm R_div_spm R_pow_spm R_lt_spm R_le_spm R_eq_spm R_gt_spm R_ge_spm
#'   R_matmult_spm R_xpose_spm R_isSymmetric_spm R_chol_spm R_sweep_spm
#'   R_scale_spm R_symeig_spm R_flrunif_spm R_flrnorm_spm R_flrand_spm R_svd_spm
#'   R_exp_spm R_expm1_spm R_log_spm R_log10_spm R_log2_spm R_sin_spm R_cos_spm
#'   R_tan_spm R_asin_spm R_acos_spm R_atan_spm R_sinh_spm R_cosh_spm R_tanh_spm
#'   R_asinh_spm R_acosh_spm R_atanh_spm R_abs_spm R_sqrt_spm R_isfinite_spm
#'   R_isinfinite_spm R_isnan_spm R_gamma_spm R_lgamma_spm R_ceiling_spm
#'   R_floor_spm R_trunc_spm R_round_spm R_solve_spm R_solve_spmspm R_norm_spm
#'   R_backsolve_spm R_colSums_spm R_rowSums_spm R_colMeans_spm R_rowMeans_spm
#'   R_isna_spm R_naomit_spm R_anyNA_spm R_sum_spm R_min_spm R_max_spm
#'   R_whichmin_spm R_whichmax_spm R_qr_spm R_qrQ_spm R_qrR_spm R_qrqy_spm
#'   R_rcond_spm R_chol2inv_spm R_spm2int
#' 
#' @docType package
#' @name float-package
#' @author Drew Schmidt
#' @keywords package
NULL
