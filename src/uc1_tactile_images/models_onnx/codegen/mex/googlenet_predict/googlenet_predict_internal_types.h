//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// googlenet_predict_internal_types.h
//
// Code generation for function 'googlenet_predict'
//

#pragma once

// Include files
#include "googlenet_predict_types.h"
#include "rtwtypes.h"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensorrtTargetNetworkImpl.hpp"
#include "emlrt.h"

// Custom Header Code

#ifdef __CUDA_ARCH__
#undef printf
#endif

// Type Definitions
class googlenet0_0 {
public:
  googlenet0_0();
  void setSize();
  void resetState();
  void setup();
  void predict();
  void cleanup();
  real32_T *getLayerOutput(int32_T layerIndex, int32_T portIndex);
  int32_T getLayerOutputSize(int32_T layerIndex, int32_T portIndex);
  real32_T *getInputDataPointer(int32_T b_index);
  real32_T *getInputDataPointer();
  real32_T *getOutputDataPointer(int32_T b_index);
  real32_T *getOutputDataPointer();
  int32_T getBatchSize();
  int32_T getOutputSequenceLength(int32_T layerIndex, int32_T portIndex);
  ~googlenet0_0();

private:
  void allocate();
  void postsetup();
  void deallocate();

public:
  boolean_T isInitialized;
  boolean_T matlabCodegenIsDeleted;

private:
  int32_T numLayers;
  MWTensorBase *inputTensors[1];
  MWTensorBase *outputTensors[1];
  MWCNNLayer *layers[144];
  MWTensorrtTarget::MWTargetNetworkImpl *targetImpl;
};

// End of code generation (googlenet_predict_internal_types.h)
