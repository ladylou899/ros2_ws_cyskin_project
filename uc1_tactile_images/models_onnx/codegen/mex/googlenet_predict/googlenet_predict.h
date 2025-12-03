//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// googlenet_predict.h
//
// Code generation for function 'googlenet_predict'
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

// Function Declarations
void googlenet_predict(const real_T cpu_in[150528], real32_T cpu_out[1000]);

void googlenet_predict_delete();

void googlenet_predict_init();

void googlenet_predict_new();

// End of code generation (googlenet_predict.h)
