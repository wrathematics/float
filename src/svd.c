// Modified from the pcapack package. Copyright (c) 2014-2017 Drew Schmidt

#include <float/float32.h>
#include <float/slapack.h>

#include "Rfloat.h"
#include "unroll.h"


int svd(const int nu, const int nv, const int m, const int n,
  float *const restrict x, float *const restrict s, float *const restrict u,
  float *const restrict vt)
{
  int jobz, info = 0;
  int lwork, *iwork;
  float tmp, *work;
  int minmn = MIN(m, n);
  int ldvt;
  
  if (nu == 0 && nv == 0)
  {
    jobz = JOBZ_N;
    ldvt = 1; // value is irrelevant, but must exist!
  }
  else if (nu <= minmn && nv <= minmn)
  {
    jobz = JOBZ_S;
    ldvt = minmn;
  }
  else
  {
    jobz = JOBZ_A;
    ldvt = n;
  }
  
  
  iwork = malloc(8*minmn * sizeof(*iwork));
  if (iwork == NULL)
  {
    free(x);
    THROW_MEMERR;
  }
  
  lwork = -1;
  F77_CALL(rgesdd)(&jobz, &m, &n, x, &m, s, u, &m, vt, &ldvt, &tmp, &lwork, iwork, &info);
  lwork = (int) tmp;
  work = malloc(lwork * sizeof(*work));
  if (work == NULL)
  {
    free(x);
    free(iwork);
    THROW_MEMERR;
  }
  
  F77_CALL(rgesdd)(&jobz, &m, &n, x, &m, s, u, &m, vt, &ldvt, work, &lwork, iwork, &info);
  
  free(work);
  free(iwork);
  
  free(x);
  
  return info;
}



SEXP R_svd_spm(SEXP x, SEXP nu_, SEXP nv_)
{
  SEXP ret, ret_names;
  SEXP s;
  SEXP u = R_NilValue, vt = R_NilValue; // avoid spurious compiler warning
  float *u_data, *vt_data;
  int nret = 1;
  const int nu = INTEGER(nu_)[0];
  const int nv = INTEGER(nv_)[0];
  const len_t m = NROWS(x);
  const len_t n = NCOLS(x);
  const len_t minmn = MIN(m, n);
  
  PROTECT(s = newvec(minmn));
  
  if (nu)
  {
    PROTECT(u = newmat(m, nu));
    nret++;
  }
  
  if (nv)
  {
    PROTECT(vt = newmat(nv, n));
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
  CHECKMALLOC(tmp);
  memcpy(tmp, DATA(x), (size_t)m*n*sizeof(*tmp));
  
  int info = svd(nu, nv, m, n, tmp, DATA(s), u_data, vt_data);
  
  if (info != 0)
    error("sgesdd() returned info=%d\n", info);
  
  
  // manage return
  PROTECT(ret = allocVector(VECSXP, nret));
  PROTECT(ret_names = allocVector(STRSXP, nret));
  
  SET_VECTOR_ELT(ret, 0, s);
  SET_STRING_ELT(ret_names, 0, mkChar("d"));
  
  int retpos = 1;
  if (nu)
  {
    if (nu != minmn && nu != m)
    {
      float *uf = FLOAT(u);
      for (int j=0; j<nu; j++)
      {
        for (len_t i=0; i<m; i++)
          uf[i + m*j] = u_data[i + m*j];
      }
    }
    
    SET_VECTOR_ELT(ret, retpos, u);
    SET_STRING_ELT(ret_names, retpos, mkChar("u"));
    retpos++;
  }
  
  if (nv)
  {
    if (nv != minmn && nv != n)
    {
      float *vtf = FLOAT(vt);
      len_t top = nv>minmn?n:minmn;
      for (len_t j=0; j<n; j++)
      {
        for (int i=0; i<nv; i++)
          vtf[i + nv*j] = vt_data[i + top*j];
      }
    }
    
    SET_STRING_ELT(ret_names, retpos, mkChar("vt"));
    SET_VECTOR_ELT(ret, retpos, vt);
    retpos++;
  }
  
  setAttrib(ret, R_NamesSymbol, ret_names);
  
  UNPROTECT((nret + 2));
  return ret;
}
