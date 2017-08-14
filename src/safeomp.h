// tl;dr: You may use the definitions in this header file as you please,
// with or without attribution. No warranty is provided.  This "license" applies
// ONLY to this particular file, and not the larger project in which it is
// contained.  If you want me to license it differently for you for some reason,
// email me.

// This file is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or distribute 
// this file, for any purpose, and by any means.
//
// In jurisdictions that recognize copyright laws, the author or authors of this 
// file dedicate any and all copyright interest in the file to the public
// domain. We make this dedication for the benefit of the public at large and to 
// the detriment of our heirs and successors. We intend this dedication to be an 
// overt act of relinquishment in perpetuity of all present and future rights to 
// this file under copyright law.
//
// THE FILE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
// WITH THIS FILE OR THE USE OR OTHER DEALINGS IN THIS FILE.
//
// For more information, please refer to http://unlicense.org/

#ifndef __COOP_LIB_OMPUTILS_H__
#define __COOP_LIB_OMPUTILS_H__

// -----------------------------------------------------------------------------
// Non-OMP vectorization stuff
// -----------------------------------------------------------------------------

// Praying to the compiler to please ignore what it thinks are loop dependencies
// and to please just go ahead and vectorize the loop already.  Useful for
// loops outside of omp parallel blocks.
// GCC HAS TO GO LAST since so many compilers support --std=gnu99 and so on
#if defined(__INTEL_COMPILER)
  #define PLEASE_VECTORIZE _Pragma("ivdep")
#elif defined(__clang__)
  #define PLEASE_VECTORIZE _Pragma("clang loop vectorize(enable) interleave(enable)")
#elif defined(__GNUC__)
  #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 9)
    #define PLEASE_VECTORIZE _Pragma("GCC ivdep")
  #else
    #define PLEASE_VECTORIZE
  #endif
#else
  #define PLEASE_VECTORIZE
#endif



// -----------------------------------------------------------------------------
// OMP stuff
// -----------------------------------------------------------------------------

#define OMP_MIN_SIZE 1000


#ifdef _OPENMP
  #include <omp.h>
  #if _OPENMP >= 201307
    #define OMP_VER_4
  #elif _OPENMP >= 200805
    #define OMP_VER_3
  #endif
#endif


// Insert SIMD pragma if supported. This pragma _demands_ vectorization, whether
// or not the compiler thinks that's a good idea.  However, it will only work
// inside of an omp parallel block.
#ifdef OMP_VER_4
  #ifdef _MSC_VER // Microsoft doing it's own non-standard bullshit? I DON'T BELIEVE IT
    #define SAFE_SIMD _pragma(omp simd)
    #define SAFE_FOR_SIMD _pragma(omp for simd)
    #define SAFE_PARALLEL_FOR_SIMD _pragma(omp parallel for simd)
  #else
    #define SAFE_SIMD _Pragma("omp simd")
    #define SAFE_FOR_SIMD _Pragma("omp for simd")
    #define SAFE_PARALLEL_FOR_SIMD _Pragma("omp parallel for simd")
  #endif
#else
  #define SAFE_SIMD PLEASE_VECTORIZE
  #define SAFE_FOR_SIMD PLEASE_VECTORIZE
  #define SAFE_PARALLEL_FOR_SIMD //TODO
#endif


#endif
