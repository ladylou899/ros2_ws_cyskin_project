//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// DeepLearningNetwork.h
//
// Code generation for function 'DeepLearningNetwork'
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
void DeepLearningNetwork_delete(googlenet0_0 *obj);

void DeepLearningNetwork_setup(googlenet0_0 *obj);

} // namespace internal
} // namespace coder

// End of code generation (DeepLearningNetwork.h)
