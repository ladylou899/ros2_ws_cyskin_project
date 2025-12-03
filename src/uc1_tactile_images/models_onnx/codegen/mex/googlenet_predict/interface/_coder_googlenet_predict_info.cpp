//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_googlenet_predict_info.cpp
//
// Code generation for function 'googlenet_predict'
//

// Include files
#include "_coder_googlenet_predict_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

// Function Declarations
static const mxArray *c_emlrtMexFcnResolvedFunctionsI();

// Function Definitions
static const mxArray *c_emlrtMexFcnResolvedFunctionsI()
{
  const mxArray *nameCaptureInfo;
  const char_T *data[4]{
      "789c6360f4f465646060e06380023608c50be50a4069260654802ecf8883860156061614"
      "7d30f97e289d9c9f57925a5102e1e425e6a6c275a6e4e766e625e695"
      "845416a43214a516e7e794a5a68065d2327352433273538391397e205eae1b92149c0392"
      "02b19d335293b3834b73198a328a112ecc41e6c0c32301877f590884",
      "073a400f0f747523c5be1964da0733df88807d30f9e8d05895dcc4929cc4a4a2fcfc1215"
      "fd92fcfc9ca4fc0afdbcbcd412fde4bc3cfde282ecf462fdf4fcfcf4"
      "9c54a0985e2eaa3b1370b8839f4877e2ca07bc0c1c60bada4d34899ef6c1c048b1af0287"
      "79c4a633311cf609a0c91b65988597a656f855e55958e61445792416",
      "fbe6e73b21dc1140c01e42ee60c0c1a7b5f90042054a12", ""};
  nameCaptureInfo = nullptr;
  emlrtNameCaptureMxArrayR2016a(&data[0], 1560U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties()
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *propFieldName[9]{"Version",
                                 "ResolvedFunctions",
                                 "Checksum",
                                 "EntryPoints",
                                 "CoverageInfo",
                                 "IsPolymorphic",
                                 "PropertyList",
                                 "UUID",
                                 "ClassEntryPointIsHandle"};
  const char_T *epFieldName[8]{
      "Name",     "NumberOfInputs", "NumberOfOutputs", "ConstantInputs",
      "FullPath", "TimeStamp",      "Constructor",     "Visible"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 8, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 1);
  emlrtSetField(xEntryPoints, 0, "Name",
                emlrtMxCreateString("googlenet_predict"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, "FullPath",
      emlrtMxCreateString(
          "/home/francesco/Documents/ROS_WORKSPACES/tactile_processing_ws/src/"
          "tactile_image_publisher_ros2/models_onnx/googlenet_predict.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739570.69391203707));
  emlrtSetField(xEntryPoints, 0, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 0, "Visible", emlrtMxCreateLogicalScalar(true));
  xResult =
      emlrtCreateStructMatrix(1, 1, 9, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("24.1.0.2603908 (R2024a) Update 3"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)c_emlrtMexFcnResolvedFunctionsI());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("2h6WuexNzn89lrZHasMooB"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

// End of code generation (_coder_googlenet_predict_info.cpp)
