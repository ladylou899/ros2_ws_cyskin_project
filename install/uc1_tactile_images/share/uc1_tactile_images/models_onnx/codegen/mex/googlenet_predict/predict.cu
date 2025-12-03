//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// predict.cu
//
// Code generation for function 'predict'
//

// Include files
#include "predict.h"
#include "DeepLearningNetwork.h"
#include "googlenet_predict_data.h"
#include "googlenet_predict_internal_types.h"
#include "googlenet_predict_mexutil.h"
#include "rt_nonfinite.h"
#include "MWCudaDimUtility.hpp"
#include "MWCudaMemoryFunctions.hpp"

// Function Declarations
static __global__ void
c_DeepLearningNetwork_predict_k(const real_T varargin_1[150528],
                                real32_T in[150528]);

static __global__ void
d_DeepLearningNetwork_predict_k(const real32_T in[150528],
                                real32_T dataInputsSingle_0_f1[150528]);

// Function Definitions
static __global__
    __launch_bounds__(512, 1) void c_DeepLearningNetwork_predict_k(
        const real_T varargin_1[150528], real32_T in[150528])
{
  int32_T i;
  i = static_cast<int32_T>(mwGetGlobalThreadIndex());
  if (i < 150528) {
    in[i] = static_cast<real32_T>(varargin_1[i]);
  }
}

static __global__
    __launch_bounds__(512, 1) void d_DeepLearningNetwork_predict_k(
        const real32_T in[150528], real32_T dataInputsSingle_0_f1[150528])
{
  uint64_T gThreadId;
  int32_T i;
  int32_T i1;
  int32_T p;
  gThreadId = mwGetGlobalThreadIndex();
  i = static_cast<int32_T>(gThreadId % 224UL);
  gThreadId = (gThreadId - static_cast<uint64_T>(i)) / 224UL;
  i1 = static_cast<int32_T>(gThreadId % 224UL);
  gThreadId = (gThreadId - static_cast<uint64_T>(i1)) / 224UL;
  p = static_cast<int32_T>(gThreadId);
  if ((p < 3) && (i1 < 224) && (i < 224)) {
    dataInputsSingle_0_f1[(i + 224 * i1) + 50176 * p] =
        in[(i1 + 224 * i) + 50176 * p];
  }
}

namespace coder {
namespace internal {
void DeepLearningNetwork_predict(googlenet0_0 *obj,
                                 const real_T varargin_1[150528],
                                 real32_T varargout_1[1000])
{
  real32_T(*gpu_dataInputsSingle_0_f1)[150528];
  real32_T(*gpu_in)[150528];
  checkCudaError(mwCudaMalloc(&gpu_dataInputsSingle_0_f1, 602112UL), __FILE__,
                 __LINE__);
  checkCudaError(mwCudaMalloc(&gpu_in, 602112UL), __FILE__, __LINE__);
  c_DeepLearningNetwork_predict_k<<<dim3(294U, 1U, 1U), dim3(512U, 1U, 1U)>>>(
      varargin_1, *gpu_in);
  d_DeepLearningNetwork_predict_k<<<dim3(294U, 1U, 1U), dim3(512U, 1U, 1U)>>>(
      *gpu_in, *gpu_dataInputsSingle_0_f1);
  checkCudaError(
      cudaMemcpy(obj->getInputDataPointer(0), *gpu_dataInputsSingle_0_f1,
                 obj->getLayerOutputSize(0, 0), cudaMemcpyDeviceToDevice),
      __FILE__, __LINE__);
  try {
    obj->predict();
  } catch (std::runtime_error const &err) {
    checkRunTimeError(err.what(), __FILE__, __LINE__);
  } catch (...) {
    checkRunTimeError("", __FILE__, __LINE__);
  }
  checkCudaError(cudaMemcpy(varargout_1, obj->getLayerOutput(143, 0),
                            obj->getLayerOutputSize(143, 0),
                            cudaMemcpyDeviceToDevice),
                 __FILE__, __LINE__);
  checkCudaError(mwCudaFree(*gpu_in), __FILE__, __LINE__);
  checkCudaError(mwCudaFree(*gpu_dataInputsSingle_0_f1), __FILE__, __LINE__);
}

} // namespace internal
} // namespace coder

// End of code generation (predict.cu)
