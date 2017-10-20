classdef CKMeanCluster
    %CKMEANCLUSTER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        TranningFileData
        TestFileData
        TestDataWOClass
        Iteration
        NoOfCluster
        ClusterMean
        ErrorValue
    end
    
    methods
        Obj = SetTranningData( Obj,TrainingData )
        Obj = SetTestData( Obj,TestData )
        Obj = SetIteration(Obj,Itr)
        Obj = SetClusterNumber(Obj,ClusterNo)
        Obj = KMeanClusterClassification(Obj)
    end
    
    methods(Access = private)
         Obj = IntializeCluster(Obj)
         Obj = ErrorClaculation(Obj);
         Obj = UpdateCluster(Obj);
    end
    
end

