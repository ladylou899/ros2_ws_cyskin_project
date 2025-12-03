% onnx model sanity check for trt conversion
clear all, close all, clc

modelfile = "HandsNet_handles_finetuned.onnx";
%params = importONNXFunction(modelfile,"HandsNetFcn");

net = importNetworkFromONNX(modelfile);
% Input is 68 x 100 x 1
% Output is 2 x 1


% re-write network as onnx model, cloud solve some compatibility issues in
% further conversions
filename = "handsnet_finetuned.onnx";
exportONNXNetwork(net,filename)