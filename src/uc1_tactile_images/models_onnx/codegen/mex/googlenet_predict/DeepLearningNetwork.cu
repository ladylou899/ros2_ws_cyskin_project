//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// DeepLearningNetwork.cu
//
// Code generation for function 'DeepLearningNetwork'
//

// Include files
#include "DeepLearningNetwork.h"
#include "googlenet_predict_data.h"
#include "googlenet_predict_internal_types.h"
#include "googlenet_predict_mexutil.h"
#include "rt_nonfinite.h"
#include "MWAvgPoolingLayer.hpp"
#include "MWCNNLayer.hpp"
#include "MWConcatenationLayer.hpp"
#include "MWConvLayer.hpp"
#include "MWElementwiseAffineLayer.hpp"
#include "MWFCLayer.hpp"
#include "MWInputLayer.hpp"
#include "MWMaxPoolingLayer.hpp"
#include "MWNormLayer.hpp"
#include "MWOutputLayer.hpp"
#include "MWReLULayer.hpp"
#include "MWSoftmaxLayer.hpp"
#include "MWTensor.hpp"
#include "MWTensorBase.hpp"
#include "MWTensorrtTargetNetworkImpl.hpp"
#include "stdlib.h"
#include "string.h"

// Function Declarations
static void checkCleanupCudaError(cudaError_t errCode, const char_T *file,
                                  uint32_T b_line);

static void checkCleanupRunTimeError(const char_T *errMsg, const char_T *file,
                                     uint32_T b_line);

namespace coder {
namespace internal {
static void DeepLearningNetwork_callDelete(googlenet0_0 *obj);

}
} // namespace coder

// Function Definitions
void googlenet0_0::allocate()
{
  targetImpl->allocate();
  for (int32_T idx{0}; idx < 144; idx++) {
    layers[idx]->allocate();
  }
}

void googlenet0_0::cleanup()
{
  try {
    isInitialized = false;
    deallocate();
    for (int32_T idx{0}; idx < 144; idx++) {
      layers[idx]->cleanup();
    }
    if (targetImpl) {
      targetImpl->cleanup();
    }
    checkCleanupCudaError(cudaGetLastError(), __FILE__, __LINE__);
  } catch (std::runtime_error const &err) {
    checkCleanupRunTimeError(err.what(), __FILE__, __LINE__);
  } catch (...) {
    checkCleanupRunTimeError("", __FILE__, __LINE__);
  }
}

void googlenet0_0::deallocate()
{
  targetImpl->deallocate();
  for (int32_T idx{0}; idx < 144; idx++) {
    layers[idx]->deallocate();
  }
}

void googlenet0_0::postsetup()
{
  int32_T activationPortIdx[1];
  int32_T activationsIdx[1];
  int32_T inputLayerIndices[1];
  int32_T rnnLayerIndices[1];
  inputLayerIndices[0] = 0;
  activationsIdx[0] = 143;
  activationPortIdx[0] = 0;
  rnnLayerIndices[0] = -1;
  targetImpl->postSetup(layers, numLayers, &inputLayerIndices[0], 1,
                        &activationsIdx[0], &activationPortIdx[0], 1,
                        &rnnLayerIndices[0], 0,
                        inputTensors[0]->getBatchSize());
  (static_cast<MWTensor<real32_T> *>(inputTensors[0]))
      ->setData(layers[0]->getLayerOutput(0));
}

void googlenet0_0::resetState()
{
}

void googlenet0_0::setSize()
{
  for (int32_T idx{0}; idx < 144; idx++) {
    layers[idx]->propagateSize();
  }
  allocate();
  postsetup();
}

void googlenet0_0::setup()
{
  if (isInitialized) {
    resetState();
  } else {
    targetImpl->preSetup();
    (static_cast<MWInputLayer *>(layers[0]))
        ->createInputLayer(targetImpl, inputTensors[0], "SSCB", -1);
    (static_cast<MWElementwiseAffineLayer *>(layers[1]))
        ->createElementwiseAffineLayer(
            targetImpl, layers[0]->getOutputTensor(0), 224, 224, 3, 224, 224, 3,
            false, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_data_scale.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_data_offset.bin",
            "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[2]))
        ->createConvLayer(
            targetImpl, layers[1]->getOutputTensor(0), 7, 7, 3, 64, 2, 2, 3, 3,
            3, 3, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_conv1-7x7_s2_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_conv1-7x7_s2_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[3]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[2]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[4]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[3]->getOutputTensor(0), 3, 3, 2, 2, 0, 1, 0, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWNormLayer *>(layers[5]))
        ->createNormLayer(targetImpl, layers[4]->getOutputTensor(0), 5, 0.0001F,
                          0.75F, 1.0F, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[6]))
        ->createConvLayer(
            targetImpl, layers[5]->getOutputTensor(0), 1, 1, 64, 64, 1, 1, 0, 0,
            0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_conv2-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_conv2-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[7]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[6]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[8]))
        ->createConvLayer(
            targetImpl, layers[7]->getOutputTensor(0), 3, 3, 64, 192, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_conv2-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_conv2-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[9]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[8]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWNormLayer *>(layers[10]))
        ->createNormLayer(targetImpl, layers[9]->getOutputTensor(0), 5, 0.0001F,
                          0.75F, 1.0F, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[11]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[10]->getOutputTensor(0), 3, 3, 2, 2, 0, 1, 0, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[12]))
        ->createConvLayer(
            targetImpl, layers[11]->getOutputTensor(0), 1, 1, 192, 64, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[13]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[12]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[14]))
        ->createConvLayer(
            targetImpl, layers[11]->getOutputTensor(0), 1, 1, 192, 96, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[15]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[14]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[16]))
        ->createConvLayer(
            targetImpl, layers[15]->getOutputTensor(0), 3, 3, 96, 128, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[17]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[16]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[18]))
        ->createConvLayer(
            targetImpl, layers[11]->getOutputTensor(0), 1, 1, 192, 16, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[19]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[18]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[20]))
        ->createConvLayer(
            targetImpl, layers[19]->getOutputTensor(0), 5, 5, 16, 32, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[21]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[20]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[22]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[11]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[23]))
        ->createConvLayer(
            targetImpl, layers[22]->getOutputTensor(0), 1, 1, 192, 32, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3a-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[24]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[23]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[25]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[13]->getOutputTensor(0),
            layers[17]->getOutputTensor(0), layers[21]->getOutputTensor(0),
            layers[24]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[26]))
        ->createConvLayer(
            targetImpl, layers[25]->getOutputTensor(0), 1, 1, 256, 128, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[27]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[26]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[28]))
        ->createConvLayer(
            targetImpl, layers[25]->getOutputTensor(0), 1, 1, 256, 128, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[29]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[28]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[30]))
        ->createConvLayer(
            targetImpl, layers[29]->getOutputTensor(0), 3, 3, 128, 192, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[31]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[30]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[32]))
        ->createConvLayer(
            targetImpl, layers[25]->getOutputTensor(0), 1, 1, 256, 32, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[33]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[32]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[34]))
        ->createConvLayer(
            targetImpl, layers[33]->getOutputTensor(0), 5, 5, 32, 96, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[35]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[34]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[36]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[25]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[37]))
        ->createConvLayer(
            targetImpl, layers[36]->getOutputTensor(0), 1, 1, 256, 64, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_3b-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[38]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[37]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[39]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[27]->getOutputTensor(0),
            layers[31]->getOutputTensor(0), layers[35]->getOutputTensor(0),
            layers[38]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[40]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[39]->getOutputTensor(0), 3, 3, 2, 2, 0, 1, 0, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[41]))
        ->createConvLayer(
            targetImpl, layers[40]->getOutputTensor(0), 1, 1, 480, 192, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[42]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[41]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[43]))
        ->createConvLayer(
            targetImpl, layers[40]->getOutputTensor(0), 1, 1, 480, 96, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[44]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[43]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[45]))
        ->createConvLayer(
            targetImpl, layers[44]->getOutputTensor(0), 3, 3, 96, 208, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[46]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[45]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[47]))
        ->createConvLayer(
            targetImpl, layers[40]->getOutputTensor(0), 1, 1, 480, 16, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[48]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[47]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[49]))
        ->createConvLayer(
            targetImpl, layers[48]->getOutputTensor(0), 5, 5, 16, 48, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[50]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[49]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[51]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[40]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[52]))
        ->createConvLayer(
            targetImpl, layers[51]->getOutputTensor(0), 1, 1, 480, 64, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4a-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[53]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[52]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[54]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[42]->getOutputTensor(0),
            layers[46]->getOutputTensor(0), layers[50]->getOutputTensor(0),
            layers[53]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[55]))
        ->createConvLayer(
            targetImpl, layers[54]->getOutputTensor(0), 1, 1, 512, 160, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[56]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[55]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[57]))
        ->createConvLayer(
            targetImpl, layers[54]->getOutputTensor(0), 1, 1, 512, 112, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[58]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[57]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[59]))
        ->createConvLayer(
            targetImpl, layers[58]->getOutputTensor(0), 3, 3, 112, 224, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[60]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[59]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[61]))
        ->createConvLayer(
            targetImpl, layers[54]->getOutputTensor(0), 1, 1, 512, 24, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[62]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[61]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[63]))
        ->createConvLayer(
            targetImpl, layers[62]->getOutputTensor(0), 5, 5, 24, 64, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[64]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[63]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[65]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[54]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[66]))
        ->createConvLayer(
            targetImpl, layers[65]->getOutputTensor(0), 1, 1, 512, 64, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4b-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[67]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[66]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[68]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[56]->getOutputTensor(0),
            layers[60]->getOutputTensor(0), layers[64]->getOutputTensor(0),
            layers[67]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[69]))
        ->createConvLayer(
            targetImpl, layers[68]->getOutputTensor(0), 1, 1, 512, 128, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[70]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[69]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[71]))
        ->createConvLayer(
            targetImpl, layers[68]->getOutputTensor(0), 1, 1, 512, 128, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[72]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[71]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[73]))
        ->createConvLayer(
            targetImpl, layers[72]->getOutputTensor(0), 3, 3, 128, 256, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[74]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[73]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[75]))
        ->createConvLayer(
            targetImpl, layers[68]->getOutputTensor(0), 1, 1, 512, 24, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[76]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[75]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[77]))
        ->createConvLayer(
            targetImpl, layers[76]->getOutputTensor(0), 5, 5, 24, 64, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[78]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[77]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[79]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[68]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[80]))
        ->createConvLayer(
            targetImpl, layers[79]->getOutputTensor(0), 1, 1, 512, 64, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4c-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[81]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[80]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[82]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[70]->getOutputTensor(0),
            layers[74]->getOutputTensor(0), layers[78]->getOutputTensor(0),
            layers[81]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[83]))
        ->createConvLayer(
            targetImpl, layers[82]->getOutputTensor(0), 1, 1, 512, 112, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[84]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[83]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[85]))
        ->createConvLayer(
            targetImpl, layers[82]->getOutputTensor(0), 1, 1, 512, 144, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[86]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[85]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[87]))
        ->createConvLayer(
            targetImpl, layers[86]->getOutputTensor(0), 3, 3, 144, 288, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[88]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[87]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[89]))
        ->createConvLayer(
            targetImpl, layers[82]->getOutputTensor(0), 1, 1, 512, 32, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[90]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[89]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[91]))
        ->createConvLayer(
            targetImpl, layers[90]->getOutputTensor(0), 5, 5, 32, 64, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[92]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[91]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[93]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[82]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[94]))
        ->createConvLayer(
            targetImpl, layers[93]->getOutputTensor(0), 1, 1, 512, 64, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4d-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[95]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[94]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[96]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[84]->getOutputTensor(0),
            layers[88]->getOutputTensor(0), layers[92]->getOutputTensor(0),
            layers[95]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[97]))
        ->createConvLayer(
            targetImpl, layers[96]->getOutputTensor(0), 1, 1, 528, 256, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[98]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[97]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[99]))
        ->createConvLayer(
            targetImpl, layers[96]->getOutputTensor(0), 1, 1, 528, 160, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[100]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[99]->getOutputTensor(0), 0,
                                              "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[101]))
        ->createConvLayer(
            targetImpl, layers[100]->getOutputTensor(0), 3, 3, 160, 320, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[102]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[101]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[103]))
        ->createConvLayer(
            targetImpl, layers[96]->getOutputTensor(0), 1, 1, 528, 32, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[104]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[103]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[105]))
        ->createConvLayer(
            targetImpl, layers[104]->getOutputTensor(0), 5, 5, 32, 128, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[106]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[105]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[107]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[96]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[108]))
        ->createConvLayer(
            targetImpl, layers[107]->getOutputTensor(0), 1, 1, 528, 128, 1, 1,
            0, 0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_4e-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[109]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[108]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[110]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[98]->getOutputTensor(0),
            layers[102]->getOutputTensor(0), layers[106]->getOutputTensor(0),
            layers[109]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[111]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[110]->getOutputTensor(0), 3, 3, 2, 2, 0, 1, 0, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[112]))
        ->createConvLayer(
            targetImpl, layers[111]->getOutputTensor(0), 1, 1, 832, 256, 1, 1,
            0, 0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[113]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[112]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[114]))
        ->createConvLayer(
            targetImpl, layers[111]->getOutputTensor(0), 1, 1, 832, 160, 1, 1,
            0, 0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[115]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[114]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[116]))
        ->createConvLayer(
            targetImpl, layers[115]->getOutputTensor(0), 3, 3, 160, 320, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[117]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[116]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[118]))
        ->createConvLayer(
            targetImpl, layers[111]->getOutputTensor(0), 1, 1, 832, 32, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[119]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[118]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[120]))
        ->createConvLayer(
            targetImpl, layers[119]->getOutputTensor(0), 5, 5, 32, 128, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[121]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[120]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[122]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[111]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[123]))
        ->createConvLayer(
            targetImpl, layers[122]->getOutputTensor(0), 1, 1, 832, 128, 1, 1,
            0, 0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5a-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[124]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[123]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[125]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[113]->getOutputTensor(0),
            layers[117]->getOutputTensor(0), layers[121]->getOutputTensor(0),
            layers[124]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[126]))
        ->createConvLayer(
            targetImpl, layers[125]->getOutputTensor(0), 1, 1, 832, 384, 1, 1,
            0, 0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-1x1_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-1x1_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[127]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[126]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[128]))
        ->createConvLayer(
            targetImpl, layers[125]->getOutputTensor(0), 1, 1, 832, 192, 1, 1,
            0, 0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-3x3_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-3x3_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[129]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[128]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[130]))
        ->createConvLayer(
            targetImpl, layers[129]->getOutputTensor(0), 3, 3, 192, 384, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-3x3_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-3x3_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[131]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[130]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[132]))
        ->createConvLayer(
            targetImpl, layers[125]->getOutputTensor(0), 1, 1, 832, 48, 1, 1, 0,
            0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-5x5_reduce_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-5x5_reduce_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[133]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[132]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[134]))
        ->createConvLayer(
            targetImpl, layers[133]->getOutputTensor(0), 5, 5, 48, 128, 1, 1, 2,
            2, 2, 2, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-5x5_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-5x5_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[135]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[134]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWMaxPoolingLayer *>(layers[136]))
        ->createMaxPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[125]->getOutputTensor(0), 3, 3, 1, 1, 1, 1, 1, 1,
            0, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConvLayer *>(layers[137]))
        ->createConvLayer(
            targetImpl, layers[136]->getOutputTensor(0), 1, 1, 832, 128, 1, 1,
            0, 0, 0, 0, 1, 1, 1,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-pool_proj_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_inception_5b-pool_proj_b.bin",
            "SSCB", -1);
    (static_cast<MWReLULayer *>(layers[138]))
        ->createReLULayer<real32_T, real32_T>(targetImpl,
                                              layers[137]->getOutputTensor(0),
                                              0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWConcatenationLayer *>(layers[139]))
        ->createConcatenationLayer(
            targetImpl, 4, layers[127]->getOutputTensor(0),
            layers[131]->getOutputTensor(0), layers[135]->getOutputTensor(0),
            layers[138]->getOutputTensor(0), 3, "C", "SSCB", -1);
    (static_cast<MWAvgPoolingLayer *>(layers[140]))
        ->createAvgPoolingLayer<real32_T, real32_T>(
            targetImpl, layers[139]->getOutputTensor(0), -1, -1, 1, 1, 0, 0, 0,
            0, 1, 0, "FLOAT", 1, "SSCB", -1);
    (static_cast<MWFCLayer *>(layers[141]))
        ->createFCLayer(
            targetImpl, layers[140]->getOutputTensor(0), 1024, 1000,
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_loss3-classifier_w.bin",
            "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/"
            "src/tactile_image_publisher_ros2/models_onnx/codegen/mex/googlene"
            "t_predict/cnn_googlenet0_0_loss3-classifier_b.bin",
            "SSCB", -1);
    (static_cast<MWSoftmaxLayer *>(layers[142]))
        ->createSoftmaxLayer(targetImpl, layers[141]->getOutputTensor(0),
                             "SSCB", -1);
    (static_cast<MWOutputLayer *>(layers[143]))
        ->createOutputLayer(targetImpl, layers[142]->getOutputTensor(0), "SSCB",
                            -1);
    outputTensors[0] = layers[143]->getOutputTensor(0);
    setSize();
  }
  isInitialized = true;
}

static void checkCleanupCudaError(cudaError_t errCode, const char_T *file,
                                  uint32_T b_line)
{
  emlrtRTEInfo rtInfo;
  if ((errCode != cudaSuccess) && (errCode != cudaErrorCudartUnloading)) {
    rtInfo = createEmlrtInfoStruct(file, b_line);
    emlrtCUDAWarning((uint32_T)errCode, (char_T *)cudaGetErrorName(errCode),
                     (char_T *)cudaGetErrorString(errCode), &rtInfo);
  }
}

static void checkCleanupRunTimeError(const char_T *errMsg, const char_T *file,
                                     uint32_T b_line)
{
  emlrtRTEInfo rtInfo;
  uint32_T errMsgLen;
  rtInfo = createEmlrtInfoStruct(file, b_line);
  errMsgLen = (uint32_T)strlen(errMsg);
  emlrtErrorWithMessageIdR2018a(emlrtRootTLSGlobal, &rtInfo,
                                "dnn_core:cnncodegen:CleanupRunTimeError",
                                "dnn_core:cnncodegen:CleanupRunTimeError", 3,
                                mxCHAR_CLASS, errMsgLen, errMsg);
}

namespace coder {
namespace internal {
static void DeepLearningNetwork_callDelete(googlenet0_0 *obj)
{
  if (obj->isInitialized) {
    obj->cleanup();
  }
}

} // namespace internal
} // namespace coder
int32_T googlenet0_0::getBatchSize()
{
  return inputTensors[0]->getBatchSize();
}

real32_T *googlenet0_0::getInputDataPointer()
{
  return (static_cast<MWTensor<real32_T> *>(inputTensors[0]))->getData();
}

real32_T *googlenet0_0::getInputDataPointer(int32_T b_index)
{
  return (static_cast<MWTensor<real32_T> *>(inputTensors[b_index]))->getData();
}

real32_T *googlenet0_0::getLayerOutput(int32_T layerIndex, int32_T portIndex)
{
  return layers[layerIndex]->getLayerOutput(portIndex);
}

int32_T googlenet0_0::getLayerOutputSize(int32_T layerIndex, int32_T portIndex)
{
  return static_cast<uint32_T>(
             layers[layerIndex]->getOutputTensor(portIndex)->getNumElements()) *
         sizeof(real32_T);
}

real32_T *googlenet0_0::getOutputDataPointer(int32_T b_index)
{
  return (static_cast<MWTensor<real32_T> *>(outputTensors[b_index]))->getData();
}

real32_T *googlenet0_0::getOutputDataPointer()
{
  return (static_cast<MWTensor<real32_T> *>(outputTensors[0]))->getData();
}

int32_T googlenet0_0::getOutputSequenceLength(int32_T layerIndex,
                                              int32_T portIndex)
{
  return layers[layerIndex]->getOutputTensor(portIndex)->getSequenceLength();
}

googlenet0_0::googlenet0_0()
{
  numLayers = 144;
  isInitialized = false;
  targetImpl = 0;
  layers[0] = new MWInputLayer;
  layers[0]->setName("data");
  layers[1] = new MWElementwiseAffineLayer;
  layers[1]->setName("data_normalization");
  layers[1]->setInPlaceIndex(0, 0);
  layers[2] = new MWConvLayer;
  layers[2]->setName("conv1-7x7_s2");
  layers[3] = new MWReLULayer;
  layers[3]->setName("conv1-relu_7x7");
  layers[3]->setInPlaceIndex(0, 0);
  layers[4] = new MWMaxPoolingLayer;
  layers[4]->setName("pool1-3x3_s2");
  layers[5] = new MWNormLayer;
  layers[5]->setName("pool1-norm1");
  layers[6] = new MWConvLayer;
  layers[6]->setName("conv2-3x3_reduce");
  layers[7] = new MWReLULayer;
  layers[7]->setName("conv2-relu_3x3_reduce");
  layers[7]->setInPlaceIndex(0, 0);
  layers[8] = new MWConvLayer;
  layers[8]->setName("conv2-3x3");
  layers[9] = new MWReLULayer;
  layers[9]->setName("conv2-relu_3x3");
  layers[9]->setInPlaceIndex(0, 0);
  layers[10] = new MWNormLayer;
  layers[10]->setName("conv2-norm2");
  layers[11] = new MWMaxPoolingLayer;
  layers[11]->setName("pool2-3x3_s2");
  layers[12] = new MWConvLayer;
  layers[12]->setName("inception_3a-1x1");
  layers[13] = new MWReLULayer;
  layers[13]->setName("inception_3a-relu_1x1");
  layers[13]->setInPlaceIndex(0, 0);
  layers[14] = new MWConvLayer;
  layers[14]->setName("inception_3a-3x3_reduce");
  layers[15] = new MWReLULayer;
  layers[15]->setName("inception_3a-relu_3x3_reduce");
  layers[15]->setInPlaceIndex(0, 0);
  layers[16] = new MWConvLayer;
  layers[16]->setName("inception_3a-3x3");
  layers[17] = new MWReLULayer;
  layers[17]->setName("inception_3a-relu_3x3");
  layers[17]->setInPlaceIndex(0, 0);
  layers[18] = new MWConvLayer;
  layers[18]->setName("inception_3a-5x5_reduce");
  layers[19] = new MWReLULayer;
  layers[19]->setName("inception_3a-relu_5x5_reduce");
  layers[19]->setInPlaceIndex(0, 0);
  layers[20] = new MWConvLayer;
  layers[20]->setName("inception_3a-5x5");
  layers[21] = new MWReLULayer;
  layers[21]->setName("inception_3a-relu_5x5");
  layers[21]->setInPlaceIndex(0, 0);
  layers[22] = new MWMaxPoolingLayer;
  layers[22]->setName("inception_3a-pool");
  layers[23] = new MWConvLayer;
  layers[23]->setName("inception_3a-pool_proj");
  layers[24] = new MWReLULayer;
  layers[24]->setName("inception_3a-relu_pool_proj");
  layers[24]->setInPlaceIndex(0, 0);
  layers[25] = new MWConcatenationLayer;
  layers[25]->setName("inception_3a-output");
  layers[26] = new MWConvLayer;
  layers[26]->setName("inception_3b-1x1");
  layers[27] = new MWReLULayer;
  layers[27]->setName("inception_3b-relu_1x1");
  layers[27]->setInPlaceIndex(0, 0);
  layers[28] = new MWConvLayer;
  layers[28]->setName("inception_3b-3x3_reduce");
  layers[29] = new MWReLULayer;
  layers[29]->setName("inception_3b-relu_3x3_reduce");
  layers[29]->setInPlaceIndex(0, 0);
  layers[30] = new MWConvLayer;
  layers[30]->setName("inception_3b-3x3");
  layers[31] = new MWReLULayer;
  layers[31]->setName("inception_3b-relu_3x3");
  layers[31]->setInPlaceIndex(0, 0);
  layers[32] = new MWConvLayer;
  layers[32]->setName("inception_3b-5x5_reduce");
  layers[33] = new MWReLULayer;
  layers[33]->setName("inception_3b-relu_5x5_reduce");
  layers[33]->setInPlaceIndex(0, 0);
  layers[34] = new MWConvLayer;
  layers[34]->setName("inception_3b-5x5");
  layers[35] = new MWReLULayer;
  layers[35]->setName("inception_3b-relu_5x5");
  layers[35]->setInPlaceIndex(0, 0);
  layers[36] = new MWMaxPoolingLayer;
  layers[36]->setName("inception_3b-pool");
  layers[37] = new MWConvLayer;
  layers[37]->setName("inception_3b-pool_proj");
  layers[38] = new MWReLULayer;
  layers[38]->setName("inception_3b-relu_pool_proj");
  layers[38]->setInPlaceIndex(0, 0);
  layers[39] = new MWConcatenationLayer;
  layers[39]->setName("inception_3b-output");
  layers[40] = new MWMaxPoolingLayer;
  layers[40]->setName("pool3-3x3_s2");
  layers[41] = new MWConvLayer;
  layers[41]->setName("inception_4a-1x1");
  layers[42] = new MWReLULayer;
  layers[42]->setName("inception_4a-relu_1x1");
  layers[42]->setInPlaceIndex(0, 0);
  layers[43] = new MWConvLayer;
  layers[43]->setName("inception_4a-3x3_reduce");
  layers[44] = new MWReLULayer;
  layers[44]->setName("inception_4a-relu_3x3_reduce");
  layers[44]->setInPlaceIndex(0, 0);
  layers[45] = new MWConvLayer;
  layers[45]->setName("inception_4a-3x3");
  layers[46] = new MWReLULayer;
  layers[46]->setName("inception_4a-relu_3x3");
  layers[46]->setInPlaceIndex(0, 0);
  layers[47] = new MWConvLayer;
  layers[47]->setName("inception_4a-5x5_reduce");
  layers[48] = new MWReLULayer;
  layers[48]->setName("inception_4a-relu_5x5_reduce");
  layers[48]->setInPlaceIndex(0, 0);
  layers[49] = new MWConvLayer;
  layers[49]->setName("inception_4a-5x5");
  layers[50] = new MWReLULayer;
  layers[50]->setName("inception_4a-relu_5x5");
  layers[50]->setInPlaceIndex(0, 0);
  layers[51] = new MWMaxPoolingLayer;
  layers[51]->setName("inception_4a-pool");
  layers[52] = new MWConvLayer;
  layers[52]->setName("inception_4a-pool_proj");
  layers[53] = new MWReLULayer;
  layers[53]->setName("inception_4a-relu_pool_proj");
  layers[53]->setInPlaceIndex(0, 0);
  layers[54] = new MWConcatenationLayer;
  layers[54]->setName("inception_4a-output");
  layers[55] = new MWConvLayer;
  layers[55]->setName("inception_4b-1x1");
  layers[56] = new MWReLULayer;
  layers[56]->setName("inception_4b-relu_1x1");
  layers[56]->setInPlaceIndex(0, 0);
  layers[57] = new MWConvLayer;
  layers[57]->setName("inception_4b-3x3_reduce");
  layers[58] = new MWReLULayer;
  layers[58]->setName("inception_4b-relu_3x3_reduce");
  layers[58]->setInPlaceIndex(0, 0);
  layers[59] = new MWConvLayer;
  layers[59]->setName("inception_4b-3x3");
  layers[60] = new MWReLULayer;
  layers[60]->setName("inception_4b-relu_3x3");
  layers[60]->setInPlaceIndex(0, 0);
  layers[61] = new MWConvLayer;
  layers[61]->setName("inception_4b-5x5_reduce");
  layers[62] = new MWReLULayer;
  layers[62]->setName("inception_4b-relu_5x5_reduce");
  layers[62]->setInPlaceIndex(0, 0);
  layers[63] = new MWConvLayer;
  layers[63]->setName("inception_4b-5x5");
  layers[64] = new MWReLULayer;
  layers[64]->setName("inception_4b-relu_5x5");
  layers[64]->setInPlaceIndex(0, 0);
  layers[65] = new MWMaxPoolingLayer;
  layers[65]->setName("inception_4b-pool");
  layers[66] = new MWConvLayer;
  layers[66]->setName("inception_4b-pool_proj");
  layers[67] = new MWReLULayer;
  layers[67]->setName("inception_4b-relu_pool_proj");
  layers[67]->setInPlaceIndex(0, 0);
  layers[68] = new MWConcatenationLayer;
  layers[68]->setName("inception_4b-output");
  layers[69] = new MWConvLayer;
  layers[69]->setName("inception_4c-1x1");
  layers[70] = new MWReLULayer;
  layers[70]->setName("inception_4c-relu_1x1");
  layers[70]->setInPlaceIndex(0, 0);
  layers[71] = new MWConvLayer;
  layers[71]->setName("inception_4c-3x3_reduce");
  layers[72] = new MWReLULayer;
  layers[72]->setName("inception_4c-relu_3x3_reduce");
  layers[72]->setInPlaceIndex(0, 0);
  layers[73] = new MWConvLayer;
  layers[73]->setName("inception_4c-3x3");
  layers[74] = new MWReLULayer;
  layers[74]->setName("inception_4c-relu_3x3");
  layers[74]->setInPlaceIndex(0, 0);
  layers[75] = new MWConvLayer;
  layers[75]->setName("inception_4c-5x5_reduce");
  layers[76] = new MWReLULayer;
  layers[76]->setName("inception_4c-relu_5x5_reduce");
  layers[76]->setInPlaceIndex(0, 0);
  layers[77] = new MWConvLayer;
  layers[77]->setName("inception_4c-5x5");
  layers[78] = new MWReLULayer;
  layers[78]->setName("inception_4c-relu_5x5");
  layers[78]->setInPlaceIndex(0, 0);
  layers[79] = new MWMaxPoolingLayer;
  layers[79]->setName("inception_4c-pool");
  layers[80] = new MWConvLayer;
  layers[80]->setName("inception_4c-pool_proj");
  layers[81] = new MWReLULayer;
  layers[81]->setName("inception_4c-relu_pool_proj");
  layers[81]->setInPlaceIndex(0, 0);
  layers[82] = new MWConcatenationLayer;
  layers[82]->setName("inception_4c-output");
  layers[83] = new MWConvLayer;
  layers[83]->setName("inception_4d-1x1");
  layers[84] = new MWReLULayer;
  layers[84]->setName("inception_4d-relu_1x1");
  layers[84]->setInPlaceIndex(0, 0);
  layers[85] = new MWConvLayer;
  layers[85]->setName("inception_4d-3x3_reduce");
  layers[86] = new MWReLULayer;
  layers[86]->setName("inception_4d-relu_3x3_reduce");
  layers[86]->setInPlaceIndex(0, 0);
  layers[87] = new MWConvLayer;
  layers[87]->setName("inception_4d-3x3");
  layers[88] = new MWReLULayer;
  layers[88]->setName("inception_4d-relu_3x3");
  layers[88]->setInPlaceIndex(0, 0);
  layers[89] = new MWConvLayer;
  layers[89]->setName("inception_4d-5x5_reduce");
  layers[90] = new MWReLULayer;
  layers[90]->setName("inception_4d-relu_5x5_reduce");
  layers[90]->setInPlaceIndex(0, 0);
  layers[91] = new MWConvLayer;
  layers[91]->setName("inception_4d-5x5");
  layers[92] = new MWReLULayer;
  layers[92]->setName("inception_4d-relu_5x5");
  layers[92]->setInPlaceIndex(0, 0);
  layers[93] = new MWMaxPoolingLayer;
  layers[93]->setName("inception_4d-pool");
  layers[94] = new MWConvLayer;
  layers[94]->setName("inception_4d-pool_proj");
  layers[95] = new MWReLULayer;
  layers[95]->setName("inception_4d-relu_pool_proj");
  layers[95]->setInPlaceIndex(0, 0);
  layers[96] = new MWConcatenationLayer;
  layers[96]->setName("inception_4d-output");
  layers[97] = new MWConvLayer;
  layers[97]->setName("inception_4e-1x1");
  layers[98] = new MWReLULayer;
  layers[98]->setName("inception_4e-relu_1x1");
  layers[98]->setInPlaceIndex(0, 0);
  layers[99] = new MWConvLayer;
  layers[99]->setName("inception_4e-3x3_reduce");
  layers[100] = new MWReLULayer;
  layers[100]->setName("inception_4e-relu_3x3_reduce");
  layers[100]->setInPlaceIndex(0, 0);
  layers[101] = new MWConvLayer;
  layers[101]->setName("inception_4e-3x3");
  layers[102] = new MWReLULayer;
  layers[102]->setName("inception_4e-relu_3x3");
  layers[102]->setInPlaceIndex(0, 0);
  layers[103] = new MWConvLayer;
  layers[103]->setName("inception_4e-5x5_reduce");
  layers[104] = new MWReLULayer;
  layers[104]->setName("inception_4e-relu_5x5_reduce");
  layers[104]->setInPlaceIndex(0, 0);
  layers[105] = new MWConvLayer;
  layers[105]->setName("inception_4e-5x5");
  layers[106] = new MWReLULayer;
  layers[106]->setName("inception_4e-relu_5x5");
  layers[106]->setInPlaceIndex(0, 0);
  layers[107] = new MWMaxPoolingLayer;
  layers[107]->setName("inception_4e-pool");
  layers[108] = new MWConvLayer;
  layers[108]->setName("inception_4e-pool_proj");
  layers[109] = new MWReLULayer;
  layers[109]->setName("inception_4e-relu_pool_proj");
  layers[109]->setInPlaceIndex(0, 0);
  layers[110] = new MWConcatenationLayer;
  layers[110]->setName("inception_4e-output");
  layers[111] = new MWMaxPoolingLayer;
  layers[111]->setName("pool4-3x3_s2");
  layers[112] = new MWConvLayer;
  layers[112]->setName("inception_5a-1x1");
  layers[113] = new MWReLULayer;
  layers[113]->setName("inception_5a-relu_1x1");
  layers[113]->setInPlaceIndex(0, 0);
  layers[114] = new MWConvLayer;
  layers[114]->setName("inception_5a-3x3_reduce");
  layers[115] = new MWReLULayer;
  layers[115]->setName("inception_5a-relu_3x3_reduce");
  layers[115]->setInPlaceIndex(0, 0);
  layers[116] = new MWConvLayer;
  layers[116]->setName("inception_5a-3x3");
  layers[117] = new MWReLULayer;
  layers[117]->setName("inception_5a-relu_3x3");
  layers[117]->setInPlaceIndex(0, 0);
  layers[118] = new MWConvLayer;
  layers[118]->setName("inception_5a-5x5_reduce");
  layers[119] = new MWReLULayer;
  layers[119]->setName("inception_5a-relu_5x5_reduce");
  layers[119]->setInPlaceIndex(0, 0);
  layers[120] = new MWConvLayer;
  layers[120]->setName("inception_5a-5x5");
  layers[121] = new MWReLULayer;
  layers[121]->setName("inception_5a-relu_5x5");
  layers[121]->setInPlaceIndex(0, 0);
  layers[122] = new MWMaxPoolingLayer;
  layers[122]->setName("inception_5a-pool");
  layers[123] = new MWConvLayer;
  layers[123]->setName("inception_5a-pool_proj");
  layers[124] = new MWReLULayer;
  layers[124]->setName("inception_5a-relu_pool_proj");
  layers[124]->setInPlaceIndex(0, 0);
  layers[125] = new MWConcatenationLayer;
  layers[125]->setName("inception_5a-output");
  layers[126] = new MWConvLayer;
  layers[126]->setName("inception_5b-1x1");
  layers[127] = new MWReLULayer;
  layers[127]->setName("inception_5b-relu_1x1");
  layers[127]->setInPlaceIndex(0, 0);
  layers[128] = new MWConvLayer;
  layers[128]->setName("inception_5b-3x3_reduce");
  layers[129] = new MWReLULayer;
  layers[129]->setName("inception_5b-relu_3x3_reduce");
  layers[129]->setInPlaceIndex(0, 0);
  layers[130] = new MWConvLayer;
  layers[130]->setName("inception_5b-3x3");
  layers[131] = new MWReLULayer;
  layers[131]->setName("inception_5b-relu_3x3");
  layers[131]->setInPlaceIndex(0, 0);
  layers[132] = new MWConvLayer;
  layers[132]->setName("inception_5b-5x5_reduce");
  layers[133] = new MWReLULayer;
  layers[133]->setName("inception_5b-relu_5x5_reduce");
  layers[133]->setInPlaceIndex(0, 0);
  layers[134] = new MWConvLayer;
  layers[134]->setName("inception_5b-5x5");
  layers[135] = new MWReLULayer;
  layers[135]->setName("inception_5b-relu_5x5");
  layers[135]->setInPlaceIndex(0, 0);
  layers[136] = new MWMaxPoolingLayer;
  layers[136]->setName("inception_5b-pool");
  layers[137] = new MWConvLayer;
  layers[137]->setName("inception_5b-pool_proj");
  layers[138] = new MWReLULayer;
  layers[138]->setName("inception_5b-relu_pool_proj");
  layers[138]->setInPlaceIndex(0, 0);
  layers[139] = new MWConcatenationLayer;
  layers[139]->setName("inception_5b-output");
  layers[140] = new MWAvgPoolingLayer;
  layers[140]->setName("pool5-7x7_s1");
  layers[141] = new MWFCLayer;
  layers[141]->setName("loss3-classifier");
  layers[142] = new MWSoftmaxLayer;
  layers[142]->setName("prob");
  layers[143] = new MWOutputLayer;
  layers[143]->setName("output");
  layers[143]->setInPlaceIndex(0, 0);
  targetImpl = new MWTensorrtTarget::MWTargetNetworkImpl;
  targetImpl->setNetworkComputePrecision(2);
  targetImpl->setIsRefittable(false);
  targetImpl->setMixedPrecisionComputeConstraint(false);
  inputTensors[0] = new MWTensor<real32_T>;
  inputTensors[0]->setHeight(224);
  inputTensors[0]->setWidth(224);
  inputTensors[0]->setChannels(3);
  inputTensors[0]->setBatchSize(1);
  inputTensors[0]->setSequenceLength(1);
}

googlenet0_0::~googlenet0_0()
{
  emlrtSetIsInDestructor((emlrtCTX *)emlrtRootTLSGlobal, true);
  try {
    if (isInitialized) {
      cleanup();
    }
    for (int32_T idx{0}; idx < 144; idx++) {
      delete layers[idx];
    }
    if (targetImpl) {
      delete targetImpl;
    }
    delete inputTensors[0];
  } catch (...) {
  }
  emlrtSetIsInDestructor((emlrtCTX *)emlrtRootTLSGlobal, false);
}

void googlenet0_0::predict()
{
  targetImpl->doInference(inputTensors[0]->getBatchSize());
}

namespace coder {
namespace internal {
void DeepLearningNetwork_delete(googlenet0_0 *obj)
{
  DeepLearningNetwork_callDelete(obj);
}

void DeepLearningNetwork_setup(googlenet0_0 *obj)
{
  try {
    obj->setup();
  } catch (std::runtime_error const &err) {
    obj->cleanup();
    checkRunTimeError(err.what(), __FILE__, __LINE__);
  } catch (...) {
    obj->cleanup();
    checkRunTimeError("", __FILE__, __LINE__);
  }
}

} // namespace internal
} // namespace coder

// End of code generation (DeepLearningNetwork.cu)
