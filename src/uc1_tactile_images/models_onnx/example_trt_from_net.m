% matlab official example for code generation
clear all, close all, clc

net = googlenet;

% check labels 
classNames = net.Layers(end).Classes;
numClasses = numel(classNames);
disp(classNames(randperm(numClasses,10)))

% check network structure (to assess input shape etc...)
% analyzeNetwork(net);


% build configuration for codegen
cfg = coder.gpuConfig('mex');
cfg.TargetLang = 'C++';
cfg.DeepLearningConfig = coder.DeepLearningConfig('tensorrt');
cfg.DeepLearningConfig.DataType = 'fp32';