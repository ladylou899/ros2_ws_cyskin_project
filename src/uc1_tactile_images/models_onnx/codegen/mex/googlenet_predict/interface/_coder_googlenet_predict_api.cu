//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_googlenet_predict_api.cu
//
// Code generation for function '_coder_googlenet_predict_api'
//

// Include files
#include "_coder_googlenet_predict_api.h"
#include "googlenet_predict.h"
#include "googlenet_predict_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static real_T (*b_emlrt_marshallIn(const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[150528];

static real_T (*emlrt_marshallIn(const mxArray *b_nullptr,
                                 const char_T *identifier))[150528];

static real_T (*emlrt_marshallIn(const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[150528];

static const mxArray *emlrt_marshallOut(const real32_T u[1000]);

// Function Definitions
static real_T (*b_emlrt_marshallIn(const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[150528]
{
  static const int32_T dims[3]{224, 224, 3};
  real_T(*ret)[150528];
  int32_T iv[3];
  boolean_T bv[3]{false, false, false};
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 3U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real_T(*)[150528])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*emlrt_marshallIn(const mxArray *b_nullptr,
                                 const char_T *identifier))[150528]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[150528];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

static real_T (*emlrt_marshallIn(const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[150528]
{
  real_T(*y)[150528];
  y = b_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *emlrt_marshallOut(const real32_T u[1000])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 1000};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

void googlenet_predict_api(const mxArray *const prhs[1], const mxArray *plhs[1])
{
  real_T(*in)[150528];
  real32_T(*out)[1000];
  out = (real32_T(*)[1000])mxMalloc(sizeof(real32_T[1000]));
  // Marshall function inputs
  in = emlrt_marshallIn(emlrtAlias(prhs[0]), "in");
  // Invoke the target function
  googlenet_predict(*in, *out);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*out);
}

// End of code generation (_coder_googlenet_predict_api.cu)
