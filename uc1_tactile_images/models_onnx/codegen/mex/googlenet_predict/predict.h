//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// predict.h
//
// Code generation for function 'predict'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Custom Header Code

#ifdef __CUDA_ARCH__
#undef printf
#endif

// Type Declarations
class googlenet0_0;

// Function Declarations
namespace coder {
namespace internal {
void DeepLearningNetwork_predict(googlenet0_0 *obj,
                                 const real_T varargin_1[150528],
                                 real32_T varargout_1[1000]);

}
} // namespace coder

// End of code generation (predict.h)
