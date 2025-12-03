//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// googlenet_predict_initialize.cu
//
// Code generation for function 'googlenet_predict_initialize'
//

// Include files
#include "googlenet_predict_initialize.h"
#include "_coder_googlenet_predict_mex.h"
#include "googlenet_predict.h"
#include "googlenet_predict_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static void googlenet_predict_once();

// Function Definitions
static void googlenet_predict_once()
{
  mex_InitInfAndNan();
  googlenet_predict_new();
  googlenet_predict_init();
}

void googlenet_predict_initialize()
{
  emlrtInitGPU(emlrtRootTLSGlobal);
  cudaGetLastError();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLicenseCheckR2022a(emlrtRootTLSGlobal,
                          "EMLRT:runTime:MexFunctionNeedsLicense",
                          "distrib_computing_toolbox", 2);
  emlrtLicenseCheckR2022a(emlrtRootTLSGlobal,
                          "EMLRT:runTime:MexFunctionNeedsLicense",
                          "neural_network_toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    googlenet_predict_once();
  }
}

// End of code generation (googlenet_predict_initialize.cu)
