#ifndef SPM_UNROLL_H_
#define SPM_UNROLL_H_


#if (defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER))
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
#endif


#endif
