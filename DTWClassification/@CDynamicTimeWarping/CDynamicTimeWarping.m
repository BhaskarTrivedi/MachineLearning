classdef CDynamicTimeWarping
    %CDTW Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        TranningFileData = struct('object_ID',{},'class_label',{},'sign_meaning',{},'dominant_hand_trajectory',{})
        TestFileData = struct('object_ID',{},'class_label',{},'sign_meaning',{},'dominant_hand_trajectory',{})
        ClassDistance;
        ClassificationAccuracy;
    end
    
    methods
        Obj = SetTranningData( Obj,TrainingData )
        Obj = SetTestData( Obj,TestData )
        Obj = Classification( Obj )
    end
    
    methods (Access = private)
        Obj = EuclideanDistance(Obj,Point1,Point2)
        OptCost = CostMat(Obj,TranningDataPath,TestDataPath)
        Obj = CalculateAccuracy(Obj,TestObjectID,TestClassID,DistMat);
    end
    

    
end

