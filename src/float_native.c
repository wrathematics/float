/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

#include <float/float32.h>

extern SEXP R_abs_spm(SEXP x);
extern SEXP R_acos_spm(SEXP x);
extern SEXP R_acosh_spm(SEXP x);
extern SEXP R_add_spm(SEXP x, SEXP y);
extern SEXP R_anyNA_spm(SEXP x);
extern SEXP R_asin_spm(SEXP x);
extern SEXP R_asinh_spm(SEXP x);
extern SEXP R_atan_spm(SEXP x);
extern SEXP R_atanh_spm(SEXP x);
extern SEXP R_backsolve_spm(SEXP x, SEXP y, SEXP upper_tri, SEXP xpose, SEXP k_);
extern SEXP R_ceiling_spm(SEXP x);
extern SEXP R_chol_spm(SEXP x);
extern SEXP R_chol2inv_spm(SEXP x, SEXP size);
extern SEXP R_colMeans_spm(SEXP x, SEXP na_rm_);
extern SEXP R_colSums_spm(SEXP x, SEXP na_rm_);
extern SEXP R_cos_spm(SEXP x);
extern SEXP R_cosh_spm(SEXP x);
extern SEXP R_crossprod_spm(SEXP x);
extern SEXP R_crossprod_spmspm(SEXP x, SEXP y);
extern SEXP R_div_spm(SEXP x, SEXP y);
extern SEXP R_eq_spm(SEXP x, SEXP y);
extern SEXP R_exp_spm(SEXP x);
extern SEXP R_expm1_spm(SEXP x);
extern SEXP R_floor_spm(SEXP x);
extern SEXP R_flrand_spm(SEXP data_, SEXP start, SEXP len_, SEXP gen_);
extern SEXP R_flrnorm_spm(SEXP m_, SEXP n_, SEXP mean_, SEXP sd_, SEXP isavec);
extern SEXP R_flrunif_spm(SEXP m_, SEXP n_, SEXP min_, SEXP max_, SEXP isavec);
extern SEXP R_gamma_spm(SEXP x);
extern SEXP R_ge_spm(SEXP x, SEXP y);
extern SEXP R_gt_spm(SEXP x, SEXP y);
extern SEXP R_init_NAf();
extern SEXP R_init_NaNf();
extern SEXP R_isSymmetric_spm(SEXP x);
extern SEXP R_isfinite_spm(SEXP x);
extern SEXP R_isinfinite_spm(SEXP x);
extern SEXP R_isna_spm(SEXP x);
extern SEXP R_isnan_spm(SEXP x);
extern SEXP R_le_spm(SEXP x, SEXP y);
extern SEXP R_lgamma_spm(SEXP x);
extern SEXP R_log10_spm(SEXP x);
extern SEXP R_log2_spm(SEXP x);
extern SEXP R_log_spm(SEXP x, SEXP base_);
extern SEXP R_lt_spm(SEXP x, SEXP y);
extern SEXP R_machine_spm();
extern SEXP R_mat2spm(SEXP x);
extern SEXP R_matmult_spm(SEXP x, SEXP y);
extern SEXP R_max_spm(SEXP x, SEXP na_rm);
extern SEXP R_min_spm(SEXP x, SEXP na_rm);
extern SEXP R_mul_spm(SEXP x, SEXP y);
extern SEXP R_naomit_spm(SEXP x);
extern SEXP R_norm_spm(SEXP x, SEXP type_);
extern SEXP R_pow_spm(SEXP x, SEXP y);
extern SEXP R_qrQ_spm(SEXP qr, SEXP qraux, SEXP complete_);
extern SEXP R_qrR_spm(SEXP qr, SEXP complete_);
extern SEXP R_qr_spm(SEXP x, SEXP tol);
extern SEXP R_qrqy_spm(SEXP qr, SEXP qraux, SEXP y, SEXP trans_);
extern SEXP R_rcond_spm(SEXP x, SEXP norm_, SEXP triang_);
extern SEXP R_round_spm(SEXP x, SEXP digits);
extern SEXP R_rowMeans_spm(SEXP x, SEXP na_rm_);
extern SEXP R_rowSums_spm(SEXP x, SEXP na_rm_);
extern SEXP R_scale_spm(SEXP x, SEXP center_, SEXP scale_);
extern SEXP R_sin_spm(SEXP x);
extern SEXP R_sinh_spm(SEXP x);
extern SEXP R_solve_spm(SEXP x);
extern SEXP R_solve_spmspm(SEXP x, SEXP y);
extern SEXP R_spm2mat(SEXP x_);
extern SEXP R_spm2int(SEXP x_);
extern SEXP R_sqrt_spm(SEXP x);
extern SEXP R_sub_spm(SEXP x, SEXP y);
extern SEXP R_sum_spm(SEXP x, SEXP na_rm);
extern SEXP R_svd_spm(SEXP x, SEXP nu_, SEXP nv_);
extern SEXP R_sweep_spm(SEXP x, SEXP MARGIN_, SEXP STATS, SEXP FUN_);
extern SEXP R_symeig_spm(SEXP x, SEXP onlyvals_, SEXP descending);
extern SEXP R_tan_spm(SEXP x);
extern SEXP R_tanh_spm(SEXP x);
extern SEXP R_tcrossprod_spm(SEXP x);
extern SEXP R_tcrossprod_spmspm(SEXP x, SEXP y);
extern SEXP R_trunc_spm(SEXP x);
extern SEXP R_whichmax_spm(SEXP x);
extern SEXP R_whichmin_spm(SEXP x);
extern SEXP R_xpose_spm(SEXP x);

static const R_CallMethodDef CallEntries[] = {
  {"R_abs_spm", (DL_FUNC) &R_abs_spm, 1},
  {"R_acos_spm", (DL_FUNC) &R_acos_spm, 1},
  {"R_acosh_spm", (DL_FUNC) &R_acosh_spm, 1},
  {"R_add_spm", (DL_FUNC) &R_add_spm, 2},
  {"R_anyNA_spm", (DL_FUNC) &R_anyNA_spm, 1},
  {"R_asin_spm", (DL_FUNC) &R_asin_spm, 1},
  {"R_asinh_spm", (DL_FUNC) &R_asinh_spm, 1},
  {"R_atan_spm", (DL_FUNC) &R_atan_spm, 1},
  {"R_atanh_spm", (DL_FUNC) &R_atanh_spm, 1},
  {"R_backsolve_spm", (DL_FUNC) &R_backsolve_spm, 5},
  {"R_ceiling_spm", (DL_FUNC) &R_ceiling_spm, 1},
  {"R_chol_spm", (DL_FUNC) &R_chol_spm, 1},
  {"R_chol2inv_spm", (DL_FUNC) &R_chol2inv_spm, 2},
  {"R_colMeans_spm", (DL_FUNC) &R_colMeans_spm, 2},
  {"R_colSums_spm", (DL_FUNC) &R_colSums_spm, 2},
  {"R_cos_spm", (DL_FUNC) &R_cos_spm, 1},
  {"R_cosh_spm", (DL_FUNC) &R_cosh_spm, 1},
  {"R_crossprod_spm", (DL_FUNC) &R_crossprod_spm, 1},
  {"R_crossprod_spmspm", (DL_FUNC) &R_crossprod_spmspm, 2},
  {"R_div_spm", (DL_FUNC) &R_div_spm, 2},
  {"R_eq_spm", (DL_FUNC) &R_eq_spm, 2},
  {"R_exp_spm", (DL_FUNC) &R_exp_spm, 1},
  {"R_expm1_spm", (DL_FUNC) &R_expm1_spm, 1},
  {"R_floor_spm", (DL_FUNC) &R_floor_spm, 1},
  {"R_flrand_spm", (DL_FUNC) &R_flrand_spm, 4},
  {"R_flrnorm_spm", (DL_FUNC) &R_flrnorm_spm, 5},
  {"R_flrunif_spm", (DL_FUNC) &R_flrunif_spm, 5},
  {"R_gamma_spm", (DL_FUNC) &R_gamma_spm, 1},
  {"R_ge_spm", (DL_FUNC) &R_ge_spm, 2},
  {"R_gt_spm", (DL_FUNC) &R_gt_spm, 2},
  {"R_init_NAf", (DL_FUNC) &R_init_NAf, 0},
  {"R_init_NaNf", (DL_FUNC) &R_init_NaNf, 0},
  {"R_isSymmetric_spm", (DL_FUNC) &R_isSymmetric_spm, 1},
  {"R_isfinite_spm", (DL_FUNC) &R_isfinite_spm, 1},
  {"R_isinfinite_spm", (DL_FUNC) &R_isinfinite_spm, 1},
  {"R_isna_spm", (DL_FUNC) &R_isna_spm, 1},
  {"R_isnan_spm", (DL_FUNC) &R_isnan_spm, 1},
  {"R_le_spm", (DL_FUNC) &R_le_spm, 2},
  {"R_lgamma_spm", (DL_FUNC) &R_lgamma_spm, 1},
  {"R_log10_spm", (DL_FUNC) &R_log10_spm, 1},
  {"R_log2_spm", (DL_FUNC) &R_log2_spm, 1},
  {"R_log_spm", (DL_FUNC) &R_log_spm, 2},
  {"R_lt_spm", (DL_FUNC) &R_lt_spm, 2},
  {"R_machine_spm", (DL_FUNC) &R_machine_spm, 0},
  {"R_mat2spm", (DL_FUNC) &R_mat2spm, 1},
  {"R_matmult_spm", (DL_FUNC) &R_matmult_spm, 2},
  {"R_max_spm", (DL_FUNC) &R_max_spm, 2},
  {"R_min_spm", (DL_FUNC) &R_min_spm, 2},
  {"R_mul_spm", (DL_FUNC) &R_mul_spm, 2},
  {"R_naomit_spm", (DL_FUNC) &R_naomit_spm, 1},
  {"R_norm_spm", (DL_FUNC) &R_norm_spm, 2},
  {"R_pow_spm", (DL_FUNC) &R_pow_spm, 2},
  {"R_qrQ_spm", (DL_FUNC) &R_qrQ_spm, 3},
  {"R_qrR_spm", (DL_FUNC) &R_qrR_spm, 2},
  {"R_qr_spm", (DL_FUNC) &R_qr_spm, 2},
  {"R_qrqy_spm", (DL_FUNC) &R_qrqy_spm, 4},
  {"R_rcond_spm", (DL_FUNC) &R_rcond_spm, 3},
  {"R_round_spm", (DL_FUNC) &R_round_spm, 2},
  {"R_rowMeans_spm", (DL_FUNC) &R_rowMeans_spm, 2},
  {"R_rowSums_spm", (DL_FUNC) &R_rowSums_spm, 2},
  {"R_scale_spm", (DL_FUNC) &R_scale_spm, 3},
  {"R_sin_spm", (DL_FUNC) &R_sin_spm, 1},
  {"R_sinh_spm", (DL_FUNC) &R_sinh_spm, 1},
  {"R_solve_spm", (DL_FUNC) &R_solve_spm, 1},
  {"R_solve_spmspm", (DL_FUNC) &R_solve_spmspm, 2},
  {"R_spm2mat", (DL_FUNC) &R_spm2mat, 1},
  {"R_spm2int", (DL_FUNC) &R_spm2int, 1},
  {"R_sqrt_spm", (DL_FUNC) &R_sqrt_spm, 1},
  {"R_sub_spm", (DL_FUNC) &R_sub_spm, 2},
  {"R_sum_spm", (DL_FUNC) &R_sum_spm, 2},
  {"R_svd_spm", (DL_FUNC) &R_svd_spm, 3},
  {"R_sweep_spm", (DL_FUNC) &R_sweep_spm, 4},
  {"R_symeig_spm", (DL_FUNC) &R_symeig_spm, 3},
  {"R_tan_spm", (DL_FUNC) &R_tan_spm, 1},
  {"R_tanh_spm", (DL_FUNC) &R_tanh_spm, 1},
  {"R_tcrossprod_spm", (DL_FUNC) &R_tcrossprod_spm, 1},
  {"R_tcrossprod_spmspm", (DL_FUNC) &R_tcrossprod_spmspm, 2},
  {"R_trunc_spm", (DL_FUNC) &R_trunc_spm, 1},
  {"R_whichmax_spm", (DL_FUNC) &R_whichmax_spm, 1},
  {"R_whichmin_spm", (DL_FUNC) &R_whichmin_spm, 1},
  {"R_xpose_spm", (DL_FUNC) &R_xpose_spm, 1},
  {NULL, NULL, 0}
};

void R_init_float(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  
  R_RegisterCCallable("float", "float_crossprod", (DL_FUNC)float_crossprod);
  R_RegisterCCallable("float", "float_tcrossprod", (DL_FUNC)float_tcrossprod);
  R_RegisterCCallable("float", "float_matmult", (DL_FUNC)float_matmult);
  R_RegisterCCallable("float", "float_symmetrize", (DL_FUNC)float_symmetrize);
  R_RegisterCCallable("float", "float_xpose", (DL_FUNC)float_xpose);
}
