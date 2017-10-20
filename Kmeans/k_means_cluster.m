function Y = k_means_cluster( FileName, NoofCluster, Iteration )
%K_MEANS_CLUSTER Summary of this function goes here
%   Detailed explanation goes here
FR = FileRead;
%FR = ReadTranningFile(FR,TranningFile);
FR = ReadTestFile(FR,FileName);

TestFileData = GetTestData(FR);


CKMeanClusterObj = CKMeanCluster;
%CKMeanClusterObj = CKMeanClusterObj.SetTranningData(TranningFileData);
CKMeanClusterObj = CKMeanClusterObj.SetTestData(TestFileData);
CKMeanClusterObj = CKMeanClusterObj.SetIteration(Iteration);
CKMeanClusterObj = CKMeanClusterObj.SetClusterNumber(NoofCluster);
CKMeanClusterObj = CKMeanClusterObj.KMeanClusterClassification();

end

