#ifndef SPM_NA_HANDLING_H_
#define SPM_NA_HANDLING_H_


#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <float/float32.h>
#include "endianness.h"


extern float NA_FLOAT;
extern float R_NaNf;


typedef union
{
  float x;
  uint16_t y[2];
} mrb;



static inline bool anyNA(const len_t len, const float *const restrict x)
{
  for (len_t i=0; i<len; i++)
  {
    if (isnan(x[i]) || ISNAf(x[i]))
      return true;
  }
  
  return false;
}


#endif
