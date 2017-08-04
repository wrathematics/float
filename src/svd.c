#include "spm.h"
#include "xpose.h"


void sgesdd_(const char *const restrict jobz, const int *const restrict m,
  const int *const restrict n, float *const restrict a,
  const int *const restrict lda, float *const restrict s,
  float *const restrict u, const int *const restrict ldu,
  float *const restrict vt, const int *const restrict ldvt,
  float *const restrict work, const int *const restrict lwork,
  int *const restrict iwork, int *const restrict info);

int svd(const int nu, const int nv, const int m, const int n,
  float *const restrict x, float *const restrict s, float *const restrict u,
  float *const restrict vt)
{
  char jobz;
  int info = 0;
  int lwork, *iwork;
  float tmp, *work;
  int minmn = MIN(m, n);
  int ldvt;
  
  if (nu == 0 && nv == 0)
  {
    jobz = 'N';
    ldvt = 1; // value is irrelevant, but must exist!
  }
  else if (nu <= minmn && nv <= minmn)
  {
    jobz = 'S';
    ldvt = minmn;
  }
  else
  {
    jobz = 'A';
    ldvt = n;
  }
  
  
  iwork = malloc(8*minmn * sizeof(*iwork));
  if (iwork == NULL)
  {
    free(x);
    error("OOM");
  }
  
  lwork = -1;
  sgesdd_(&jobz, &m, &n, x, &m, s, u, &m, vt, &ldvt, &tmp, &lwork, iwork, &info);
  lwork = (int) tmp;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    free(x);
    free(iwork);
    error("OOM");
  }
  
  sgesdd_(&jobz, &m, &n, x, &m, s, u, &m, vt, &ldvt, work, &lwork, iwork, &info);
  
  free(work);
  free(iwork);
  
  free(x);
  
  return info;
}



SEXP R_svd_spm(SEXP x_ptr, SEXP nu_, SEXP nv_)
{
  SEXP ret, ret_names;
  SEXP s_ptr;
  SEXP u_ptr = R_NilValue, vt_ptr = R_NilValue; // avoid spurious compiler warning
  matrix_t *s;
  matrix_t *u = NULL, *vt = NULL; // avoid spurious compiler warning
  float *u_data, *vt_data;
  int nret = 1;
  const int nu = INTEGER(nu_)[0];
  const int nv = INTEGER(nv_)[0];
  matrix_t *x = (matrix_t*) getRptr(x_ptr);
  const int m = NROWS(x);
  const int n = NCOLS(x);
  const int minmn = MIN(m, n);
  
  s = newvec(minmn);
  newRptr(s, s_ptr, matfin);
  
  if (nu)
  {
    u = newmat(m, nu);
    newRptr(u, u_ptr, matfin);
    nret++;
  }
  
  if (nv)
  {
    vt = newmat(nv, n);
    newRptr(vt, vt_ptr, matfin);
    nret++;
  }
  
  if (nu || nv)
  {
    if (nu > minmn || nv > minmn)
    {
      if (nu == m)
        u_data = DATA(u);
      else
        u_data = (float*) R_alloc(m*m, sizeof(*u_data));
      
      if (nv == n)
        vt_data = DATA(vt);
      else
        vt_data = (float*) R_alloc(n*n, sizeof(*vt_data));
    }
    else
    {
      if (nu == minmn)
        u_data = DATA(u);
      else
        u_data = (float*) R_alloc(m*minmn, sizeof(*u_data));
      
      if (nv == minmn)
        vt_data = DATA(vt);
      else
        vt_data = (float*) R_alloc(minmn*n, sizeof(*vt_data));
    }
  }
  else
  {
    u_data = NULL;
    vt_data = NULL;
  }
  
  
  float *tmp = malloc(m*n * sizeof(*tmp));
  if (tmp == NULL)
    error("OOM");
  memcpy(tmp, DATA(x), (size_t)m*n*sizeof(*tmp));
  
  int info = svd(nu, nv, m, n, tmp, DATA(s), u_data, vt_data);
  
  if (info != 0)
    error("sgesdd() returned info=%d\n", info);
  
  
  // manage return
  PROTECT(ret = allocVector(VECSXP, nret));
  PROTECT(ret_names = allocVector(STRSXP, nret));
  
  SET_VECTOR_ELT(ret, 0, s_ptr);
  SET_STRING_ELT(ret_names, 0, mkChar("d"));
  
  int retpos = 1;
  if (nu)
  {
    if (nu != minmn && nu != m)
    {
      for (int j=0; j<nu; j++)
      {
        for (int i=0; i<m; i++)
          DATA(u)[i + m*j] = u_data[i + m*j];
      }
    }
    
    SET_VECTOR_ELT(ret, retpos, u_ptr);
    SET_STRING_ELT(ret_names, retpos, mkChar("u"));
    retpos++;
  }
  
  if (nv)
  {
    if (nv != minmn && nv != n)
    {
      int top = nv>minmn?n:minmn;
      for (int j=0; j<n; j++)
      {
        for (int i=0; i<nv; i++)
          DATA(vt)[i + nv*j] = vt_data[i + top*j];
      }
    }
    
    SET_STRING_ELT(ret_names, retpos, mkChar("vt"));
    SET_VECTOR_ELT(ret, retpos, vt_ptr);
    retpos++;
  }
  
  setAttrib(ret, R_NamesSymbol, ret_names);
  
  UNPROTECT((nret + 2));
  return ret;
}
