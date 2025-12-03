//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// googlenet_predict.cu
//
// Code generation for function 'googlenet_predict'
//

// Include files
#include "googlenet_predict.h"
#include "DeepLearningNetwork.h"
#include "googlenet_predict_internal_types.h"
#include "googlenet_predict_mexutil.h"
#include "predict.h"
#include "rt_nonfinite.h"
#include "MWCudaMemoryFunctions.hpp"

// Variable Definitions
static googlenet0_0 mynet;

static boolean_T mynet_not_empty;

// Function Definitions
void googlenet_predict(const real_T cpu_in[150528], real32_T cpu_out[1000])
{
  real_T(*gpu_in)[150528];
  real32_T(*gpu_out)[1000];
  checkCudaError(mwCudaMalloc(&gpu_out, 4000UL), __FILE__, __LINE__);
  checkCudaError(mwCudaMalloc(&gpu_in, 1204224UL), __FILE__, __LINE__);
  if (!mynet_not_empty) {
    coder::internal::DeepLearningNetwork_setup(&mynet);
    mynet.matlabCodegenIsDeleted = false;
    mynet_not_empty = true;
  }
  //  pass in input
  checkCudaError(cudaMemcpy(*gpu_in, cpu_in, 1204224UL, cudaMemcpyHostToDevice),
                 __FILE__, __LINE__);
  coder::internal::DeepLearningNetwork_predict(&mynet, *gpu_in, *gpu_out);
  checkCudaError(cudaMemcpy(cpu_out, *gpu_out, 4000UL, cudaMemcpyDeviceToHost),
                 __FILE__, __LINE__);
  checkCudaError(mwCudaFree(*gpu_in), __FILE__, __LINE__);
  checkCudaError(mwCudaFree(*gpu_out), __FILE__, __LINE__);
}

void googlenet_predict_delete()
{
  if (!mynet.matlabCodegenIsDeleted) {
    mynet.matlabCodegenIsDeleted = true;
    coder::internal::DeepLearningNetwork_delete(&mynet);
  }
}

void googlenet_predict_init()
{
  mynet_not_empty = false;
}

void googlenet_predict_new()
{
  mynet.matlabCodegenIsDeleted = true;
}

// End of code generation (googlenet_predict.cu)
