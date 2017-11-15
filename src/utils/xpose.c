// Taken from the coop package. Copyright (c) 2016-2017 Drew Schmidt

void float_xpose(const int m, const int n, const float *const restrict x, float *const restrict tx)
{
  const int blocksize = 8; // TODO check cache line explicitly
  
  for (int j=0; j<n; j+=blocksize)
  {
    for (int i=0; i<m; i+=blocksize)
    {
      for (int col=j; col<j+blocksize && col<n; ++col)
      {
        for (int row=i; row<i+blocksize && row<m; ++row)
          tx[col + n*row] = x[row + m*col];
      }
    }
  }
}
