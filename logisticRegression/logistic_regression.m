function y = logistic_regression( TranningFile, Degree, TestFile )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
%set(0,'DefaultFigureVisible','off')
FR = FileRead;
FR = ReadTranningFile(FR,TranningFile);
FR = ReadTestFile(FR,TestFile);
TranningFileData = GetTranningData(FR);
TestFileData = GetTestData(FR);

LR = LogisticRegression;
LR = SetDegree(LR,Degree);
LR = SetTranningData(LR,TranningFileData);
LR = SetTestData(LR,TestFileData);
LR = LogRegression(LR);
end

