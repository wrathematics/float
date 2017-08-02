#include <stdint.h>
#include <string.h>

#include "endianness.h"
#include "spm.h"

// R uses 0x7ff00000000007a2 for NA_REAL, and 0x7f8007a2 is the most reasonable
// float analogue
float NA_FLOAT;

static inline float get_na_float()
{
  float ret;
  
#if SPM_BOBE
  int32_t x = 0xa207807f;
#else
  int32_t x = 0x7f8007a2;
#endif
  
  memcpy((void*) &ret, (void*) &x, sizeof(float));
  
  return ret;
}



SEXP R_init_NA()
{
  NA_FLOAT = get_na_float();
  return R_NilValue;
}
