classdef CKNearestNeighbour
    %CPCAPOWER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        TranningFileData
        TestFileData
        NormTranningFileData
        NormTestFileData
        NearestNeighbourCount
        Dimension
        ClassField
    end
    
    methods
        Obj = SetTranningData( Obj,TrainingData )
        Obj = SetTestData( Obj,TestData )
        Obj = SetNearestNeighbour(Obj,Itr)
        Obj = Normalization(Obj)
        Obj = Classification(Obj)
    end
    methods(Access = private)
        
    end
    
end

