function out = googlenet_predict(in) %#codegen

persistent mynet;

if isempty(mynet)
    mynet = coder.loadDeepLearningNetwork('googlenet');
end

% pass in input   
out = predict(mynet,in); 