//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// googlenet_predict_mexutil.cu
//
// Code generation for function 'googlenet_predict_mexutil'
//

// Include files
#include "googlenet_predict_mexutil.h"
#include "googlenet_predict_data.h"
#include "rt_nonfinite.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Function Definitions
void checkCudaError(cudaError_t errCode, const char_T *file, uint32_T b_line)
{
  if (errCode != cudaSuccess) {
    raiseCudaError(errCode, file, b_line, cudaGetErrorName(errCode),
                   cudaGetErrorString(errCode));
  }
}

void checkRunTimeError(const char_T *errMsg, const char_T *file,
                       uint32_T b_line)
{
  emlrtRTEInfo rtInfo;
  uint32_T errMsgLen;
  rtInfo = createEmlrtInfoStruct(file, b_line);
  errMsgLen = (uint32_T)strlen(errMsg);
  emlrtErrorWithMessageIdR2018a(
      emlrtRootTLSGlobal, &rtInfo, "dnn_core:cnncodegen:RunTimeError",
      "dnn_core:cnncodegen:RunTimeError", 3, mxCHAR_CLASS, errMsgLen, errMsg);
}

emlrtRTEInfo createEmlrtInfoStruct(const char_T *file, uint32_T b_line)
{
  emlrtRTEInfo b_rtInfo;
  uint32_T len;
  char_T *brk;
  char_T *fn;
  char_T *pn;
  len = (uint32_T)strlen(file);
  pn = static_cast<char_T *>(calloc(len + 1U, 1U));
  fn = static_cast<char_T *>(calloc(len + 1U, 1U));
  memcpy(pn, file, len);
  memcpy(fn, file, len);
  brk = strrchr(fn, '.');
  *brk = '\x00';
  brk = strrchr(fn, '/');
  if (brk == nullptr) {
    brk = strrchr(fn, '\\');
  }
  if (brk == nullptr) {
    brk = fn;
  } else {
    brk++;
  }
  b_rtInfo.lineNo = static_cast<int32_T>(b_line);
  b_rtInfo.colNo = 0;
  b_rtInfo.fName = brk;
  b_rtInfo.pName = pn;
  return b_rtInfo;
}

void raiseCudaError(int32_T errCode, const char_T *file, uint32_T b_line,
                    const char_T *errorName, const char_T *errorString)
{
  emlrtRTEInfo rtInfo;
  uint64_T len;
  char_T *brk;
  char_T *fn;
  char_T *pn;
  len = strlen(file);
  pn = static_cast<char_T *>(calloc(len + 1UL, 1UL));
  fn = static_cast<char_T *>(calloc(len + 1UL, 1UL));
  memcpy(pn, file, len);
  memcpy(fn, file, len);
  brk = strrchr(fn, '.');
  *brk = '\x00';
  brk = strrchr(fn, '/');
  if (brk == nullptr) {
    brk = strrchr(fn, '\\');
  }
  if (brk == nullptr) {
    brk = fn;
  } else {
    brk++;
  }
  rtInfo.lineNo = static_cast<int32_T>(b_line);
  rtInfo.colNo = 0;
  rtInfo.fName = brk;
  rtInfo.pName = pn;
  emlrtCUDAError(static_cast<uint32_T>(errCode), (char_T *)errorName,
                 (char_T *)errorString, &rtInfo, emlrtRootTLSGlobal);
}

// End of code generation (googlenet_predict_mexutil.cu)
