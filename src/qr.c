#include "spm.h"


// no pivoting
void sgeqrf_(const int *const restrict m, const int *const restrict n, 
  float *const restrict a, const int *const restrict lda,
  float *const restrict tau, float *const restrict work,
  const int *const restrict lwork, int *const restrict info);

// with pivoting
void sgeqp3_(const int *const restrict m, const int *const restrict n, 
  float *const restrict a, const int *const restrict lda,
  int *const restrict jpvt, float *const restrict tau,
  float *const restrict work, const int *const restrict lwork,
  int *const restrict info);

// recover Q
void sorgqr_(const int *const restrict m, const int *const restrict n,
  const int *const restrict k, float *const restrict a, 
  const int *const restrict lda, float *const restrict tau,
  float *const restrict work, const int *const restrict lwork,
  int *const restrict info);



static inline int worksize(const int m, const int n)
{
  int lwork;
  float tmp;
  
  sgeqp3_(&m, &n, &(float){0}, &m, &(int){0}, &(float){0}, &tmp, &(int){-1}, &(int){0});
  lwork = (int) tmp;
  
  return MAX(lwork, 1);
}

static inline int get_rank(const int m, const int n, const float *const restrict qr, const double tol)
{
  const float minval = fabsf((float) tol*qr[0]);
  const int minmn = MIN(m, n);
  
  for (int i=1; i<minmn; i++)
  {
    if (fabsf(qr[i + m*i]) < minval)
      return i;
  }
  
  return minmn;
}



SEXP R_qr_spm(SEXP x, SEXP tol)
{
  SEXP qrlist, qrlist_names;
  SEXP qr, rank, qraux, pivot;
  int info;
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const len_t minmn = MIN(m, n);
  
  PROTECT(rank = allocVector(INTSXP, 1));
  PROTECT(pivot = allocVector(INTSXP, n));
  
  PROTECT(qr = newmat(m, n));
  PROTECT(qraux = newvec(minmn));
  
  
  int lwork = worksize(m, n);
  float *work = malloc(lwork * sizeof(*work));
  if (work == NULL)
    error("OOM");
  
  memcpy(DATA(qr), DATA(x), (size_t)m*n*sizeof(float));
  memset(INTEGER(pivot), 0, n*sizeof(int));
  
  sgeqp3_(&m, &n, DATA(qr), &m, INTEGER(pivot), DATA(qraux), work, &lwork, &info);
  
  free(work);
  
  if (info != 0)
    error("sgeqp3() returned info=%d\n", info);
  
  INTEGER(rank)[0] = get_rank(m, n, DATA(qr), REAL(tol)[0]);
  
  PROTECT(qrlist_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(qrlist_names, 0, mkChar("qr"));
  SET_STRING_ELT(qrlist_names, 1, mkChar("rank"));
  SET_STRING_ELT(qrlist_names, 2, mkChar("qraux"));
  SET_STRING_ELT(qrlist_names, 3, mkChar("pivot"));
  
  PROTECT(qrlist = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(qrlist, 0, qr);
  SET_VECTOR_ELT(qrlist, 1, rank);
  SET_VECTOR_ELT(qrlist, 2, qraux);
  SET_VECTOR_ELT(qrlist, 3, pivot);
  
  setAttrib(qrlist, R_NamesSymbol, qrlist_names);
  
  classgets(qrlist, mkString("qr"));
  UNPROTECT(6);
  return qrlist;
}



SEXP R_qrQ_spm(SEXP qr, SEXP tau)
{
  SEXP Q;
  int info;
  const len_t m = NROWS(qr);
  const len_t n = NCOLS(qr);
  const len_t minmn = MIN(m, n);
  
  PROTECT(Q = newmat(m, minmn));
  
  len_t k = minmn;
  
  float tmp;
  sorgqr_(&m, &minmn, &k, DATA(Q), &m, DATA(tau), &tmp, &(int){-1}, &info);
  int lwork = (int) tmp;
  float *work = malloc(lwork * sizeof(*work));
  if (work == NULL)
    error("OOM");
  
  memcpy(DATA(Q), DATA(qr), (size_t)m*minmn*sizeof(float));
  
  sorgqr_(&m, &minmn, &k, DATA(Q), &m, DATA(tau), work, &lwork, &info);
  
  free(work);
  
  if (info != 0)
    error("sorgqr() returned info=%d\n", info);
  
  UNPROTECT(1);
  return Q;
}



SEXP R_qrR_spm(SEXP qr, SEXP complete_)
{
  SEXP R;
  const len_t m = NROWS(qr);
  const len_t n = NCOLS(qr);
  const int complete = INTEGER(complete_)[0];
  const len_t nrows = complete ? m : MIN(m, n);
  
  PROTECT(R = newmat(nrows, n));
  float *qrf = FLOAT(qr);
  float *Rf = FLOAT(R);
  
  memset(Rf, 0, (size_t)nrows*n*sizeof(float));
  for (len_t j=0; j<n; j++)
  {
    for (len_t i=0; i<=j && i<nrows; i++)
      Rf[i + nrows*j] = qrf[i + m*j];
  }
  
  UNPROTECT(1);
  return R;
}
