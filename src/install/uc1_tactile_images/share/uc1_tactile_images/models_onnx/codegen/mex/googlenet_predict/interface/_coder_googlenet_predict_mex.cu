//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_googlenet_predict_mex.cu
//
// Code generation for function '_coder_googlenet_predict_mex'
//

// Include files
#include "_coder_googlenet_predict_mex.h"
#include "_coder_googlenet_predict_api.h"
#include "googlenet_predict_data.h"
#include "googlenet_predict_initialize.h"
#include "googlenet_predict_terminate.h"
#include "rt_nonfinite.h"
#include <stdexcept>

void emlrtExceptionBridge();
void emlrtExceptionBridge()
{
  throw std::runtime_error("");
}
// Function Definitions
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&googlenet_predict_atexit);
  // Module initialization.
  googlenet_predict_initialize();
  try { // Dispatch the entry-point.
    unsafe_googlenet_predict_mexFunction(nlhs, plhs, nrhs, prhs);
    // Module termination.
    googlenet_predict_terminate();
  } catch (...) {
    emlrtCleanupOnException((emlrtCTX *)emlrtRootTLSGlobal);
    throw;
  }
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           (void *)&emlrtExceptionBridge, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

void unsafe_googlenet_predict_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                          int32_T nrhs, const mxArray *prhs[1])
{
  const mxArray *outputs[1];
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 1, 4, 17, "googlenet_predict");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "googlenet_predict");
  }
  // Call the function.
  googlenet_predict_api(prhs, outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs[0]);
}

// End of code generation (_coder_googlenet_predict_mex.cu)
