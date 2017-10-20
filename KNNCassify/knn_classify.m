function Y = knn_classify( TranningFile,TestFile,NeighbourCount )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
FR = FileRead;
FR = ReadTranningFile(FR,TranningFile);
FR = ReadTestFile(FR,TestFile);
TranningFileData = GetTranningData(FR);
TestFileData = GetTestData(FR);

KNearestNeighbourObj = CKNearestNeighbour;
KNearestNeighbourObj = KNearestNeighbourObj.SetTranningData(TranningFileData);
KNearestNeighbourObj = KNearestNeighbourObj.SetTestData(TestFileData);
KNearestNeighbourObj = KNearestNeighbourObj.SetNearestNeighbour(NeighbourCount);
KNearestNeighbourObj = KNearestNeighbourObj.Normalization();
KNearestNeighbourObj = KNearestNeighbourObj.Classification();
%PCAObj = PCAObj.PCATest();
%disp(TranningFileData);

end

