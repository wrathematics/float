#ifndef SPM_MATMULT_
#define SPM_MATMULT_


void sgemm_(const char *transa, const char *transb, const int *m, const int *n,
            const int *k, const float *restrict alpha, const float *restrict a,
            const int *lda, const float *restrict b, const int *ldb,
            const float *beta, float *restrict c, const int *ldc);

// dgemm wrapper
static inline void matmult(const bool transx, const bool transy, const float alpha, const int mx, const int nx, const float *const restrict x, const int my, const int ny, const float *const restrict y, float *restrict ret)
{
  // m = # rows of op(x)
  // n = # cols of op(y)
  // k = # cols of op(x)
  int im, in, ik;
  char ctransx, ctransy;
  static const float zero = 0.;
  
  ctransx = transx ? 'T' : 'N';
  ctransy = transy ? 'T' : 'N';
  
  if (transx)
  {
    im = nx;
    ik = mx;
  }
  else
  {
    im = mx;
    ik = nx;
  }
  
  in = transy ? my : ny;
  
  sgemm_(&ctransx, &ctransy, &im, &in, &ik, &alpha, x, &mx, y, &my, &zero, ret, &im);
}


#endif
