function Y = neural_network( TranningFile, TestFile,Layers,UnitsperLayes,rounds )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

FR = FileRead;
FR = ReadTranningFile(FR,TranningFile);
FR = ReadTestFile(FR,TestFile);
TranningFileData = GetTranningData(FR);
TestFileData = GetTestData(FR);

NWObj = CNeuralNetwork;
NWObj = SetTranningData(NWObj,TranningFileData);
NWObj = SetTestData(NWObj,TestFileData);
NWObj = NWObj.SetRounds(rounds);
NWObj = NWObj.SetPerceptronPerLayers(UnitsperLayes);
NWObj = NWObj.SetLayers(Layers);
NWObj = NWObj.NeuralNetworkTranning();
NWObj = NWObj.Classification();
end

