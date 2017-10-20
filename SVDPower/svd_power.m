function Y = pca_power( TranningFile,OutputDimension,Iteration )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
FR = FileRead;
FR = ReadTranningFile(FR,TranningFile);
%FR = ReadTestFile(FR,TestFile);
TranningFileData = GetTranningData(FR);
TestFileData = GetTestData(FR);

SVDObj = CSVDPower;
SVDObj = SVDObj.SetTranningData(TranningFileData);
SVDObj = SVDObj.SetTestData(TestFileData);
SVDObj = SVDObj.SetOutputDimension(OutputDimension);
SVDObj = SVDObj.SetIteration(Iteration);
SVDObj = SVDObj.SVDTranning();
%PCAObj = PCAObj.PCATest();
%disp(TranningFileData);

end

