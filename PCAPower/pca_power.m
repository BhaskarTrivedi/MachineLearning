function Y = pca_power( TranningFile, TestFile,OutputDimension,Iteration )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
FR = FileRead;
FR = ReadTranningFile(FR,TranningFile);
FR = ReadTestFile(FR,TestFile);
TranningFileData = GetTranningData(FR);
TestFileData = GetTestData(FR);

PCAObj = CPCAPower;
PCAObj = PCAObj.SetTranningData(TranningFileData);
PCAObj = PCAObj.SetTestData(TestFileData);
PCAObj = PCAObj.SetOutputDimension(OutputDimension);
PCAObj = PCAObj.SetIteration(Iteration);
PCAObj = PCAObj.PCATranning();
PCAObj = PCAObj.PCATest();
%disp(TranningFileData);

end

