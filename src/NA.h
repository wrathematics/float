#ifndef SPM_NA_HANDLING_H_
#define SPM_NA_HANDLING_H_


#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "endianness.h"


typedef union
{
  float x;
  uint16_t y[2];
} mrb;

static inline int ISNAf(const float x)
{
  if (!isnan(x))
    return 0;
  
  mrb y;
  y.x = x;
  
#if SPM_BOBE
  return y.y[1] == 1954;
#else
  return y.y[0] == 1954;
#endif
}



static inline int ISNANf(const float x)
{
  return isnan(x) && !ISNAf(x);
}



static inline bool anyNA(const size_t len, const float *const restrict x)
{
  for (size_t i=0; i<len; i++)
  {
    if (isnan(x[i]) || ISNAf(x[i]))
      return true;
  }
  
  return false;
}


#endif
