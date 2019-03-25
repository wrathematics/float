#ifndef R_FLOAT_LAPACK_
#define R_FLOAT_LAPACK_

#include <R_ext/RS.h> // for F77_NAME

#ifdef __cplusplus
  #ifndef restrict
    #define restrict
  #endif
#endif


// -----------------------------------------------------------------------------
// Wrappers to fix a portability issue with passing characters from C on
// C windows gfortran. See also wrap.f
// -----------------------------------------------------------------------------

#define UPLO_L 0 // lower triangular
#define UPLO_U 1 // upper triangular

#define TRANS_N 0 // no transpose
#define TRANS_T 1 // transpose

#define DIAG_N 0 // non-unit triangular
#define DIAG_U 1 // unit triangular

#define NORM_O 0 // 1-norm
#define NORM_I 1 // infinity-norm

#define JOBZ_N 0 // singular/eigen-values only
#define JOBZ_V 1 // eigenvalues and eigenvectors
#define JOBZ_A 2 // all left/right singular vectors
#define JOBZ_S 3 // 
#define JOBZ_O 4 // 

#define RANGE_A 0 // all eigenvalues
#define RANGE_V 1 // all eigenvalues in the (VL, VU] interval
#define RANGE_T 2 // IL'th through IU'th eigenvalues

#define SIDE_L 0 // left
#define SIDE_R 1 // right



#ifdef __cplusplus
extern "C" {
#endif

// ------------------   blas   ------------------

// ssyrk - crossprod
void F77_NAME(rsyrk)(const int *uplo, const int *trans, const int *n, const int *k,
  const float *restrict alpha, const float *restrict a, const int *lda,
  const float *restrict beta, float *restrict c, const int *ldc);

// matrix multiply
void F77_NAME(rgemm)(const int *transa, const int *transb, const int *m, const int *n,
  const int *k, const float *restrict alpha, const float *restrict a,
  const int *lda, const float *restrict b, const int *ldb,
  const float *beta, float *restrict c, const int *ldc);


// ------------------   lapack   ------------------

// strtrs - solve triangular system
void F77_NAME(rtrtrs)(const int *const restrict uplo, const int *const restrict trans,
  const int *const restrict diag, const int *const restrict n,
  const int *const restrict nrhs, const float *const restrict a,
  const int *const restrict lda, float *const restrict b,
  const int *const restrict ldb, int *const restrict info);

// spotrf - cholesky
void F77_NAME(rpotrf)(const int *const restrict uplo, const int *const restrict n,
  float *const restrict a, const int *const restrict lda,
  int *const restrict info);

// strcon - reciprocal condition number of triangular matrix
void F77_NAME(rtrcon)(const int *const restrict norm, const int *const restrict uplo,
  const int *const restrict diag, const int *const restrict n,
  const float *const restrict a, const int *const restrict lda,
  float *const restrict rcond, float *const restrict work,
  int *const restrict iwork, int *const restrict info);

// sgecon - reciprocal condition number of general matrix
void F77_NAME(rgecon)(const int *const restrict norm, const int *const restrict n,
  const float *const restrict a, const int *const restrict lda,
  const float *const restrict anorm, float *const restrict rcond,
  float *const restrict work, int *const restrict iwork,
  int *const restrict info);

// LU
void F77_NAME(sgetrf)(const int *const restrict m, const int *const restrict n,
  float *const restrict a, const int *const restrict lda,
  int *const restrict ipiv, int *const restrict info);

// eigen
void F77_NAME(rsyevr)(const int * const restrict, const int *const restrict, 
  const int *const restrict, const int *const restrict, float *const restrict,
  const int *const restrict, const float *const restrict,
  const float *const restrict, const int *const restrict,
  const int *const restrict, const float *const restrict,
  const int *const restrict, float *const restrict, float *const restrict,
  const int *const restrict, int *const restrict, float *const restrict,
  int *const restrict, int *const restrict, int *const restrict,
  int *const restrict);

// 
void F77_NAME(slassq)(const int *const restrict n, const float *const restrict x,
  const int *const restrict incx, float *const restrict scale,
  float *const restrict sumsq);

// QR: no pivoting
void F77_NAME(sgeqrf)(const int *const restrict m, const int *const restrict n, 
  float *const restrict a, const int *const restrict lda,
  float *const restrict tau, float *const restrict work,
  const int *const restrict lwork, int *const restrict info);

// QR: with pivoting
void F77_NAME(sgeqp3)(const int *const restrict m, const int *const restrict n, 
  float *const restrict a, const int *const restrict lda,
  int *const restrict jpvt, float *const restrict tau,
  float *const restrict work, const int *const restrict lwork,
  int *const restrict info);

// QR: recover Q
void F77_NAME(sorgqr)(const int *const restrict m, const int *const restrict n,
  const int *const restrict k, float *const restrict a, 
  const int *const restrict lda, float *const restrict tau,
  float *const restrict work, const int *const restrict lwork,
  int *const restrict info);

// QR: Q * c
void F77_NAME(rormqr)(const int *const restrict side, const int *const restrict trans,
  const int *const restrict m, const int *const restrict n,
  const int *const restrict k, const float *const restrict a,
  const int *const restrict lda, const float *const restrict tau,
  float *const restrict c, const int *const restrict ldc,
  float *const restrict work, const int *const restrict lwork,
  int *const restrict info);

// svd
void F77_NAME(rgesdd)(const int *const restrict jobz, const int *const restrict m,
  const int *const restrict n, float *const restrict a,
  const int *const restrict lda, float *const restrict s,
  float *const restrict u, const int *const restrict ldu,
  float *const restrict vt, const int *const restrict ldvt,
  float *const restrict work, const int *const restrict lwork,
  int *const restrict iwork, int *const restrict info);

// chol2inv
void F77_NAME(rpotri)(const int *const restrict uplo, const int *const restrict n,
  float *const restrict a, const int *const restrict lda,
  int *const restrict info);


#ifdef __cplusplus
}
#endif

#endif
