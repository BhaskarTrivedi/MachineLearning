classdef CSVDPower
    %CPCAPOWER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        TranningFileData
        TestFileData
        MatU 
        MatS 
        MatV
        OutputDimension
        Iteration
        Dimension
        EgnVec
        EgnValues
        MatReconstruction
    end
    
    methods
        Obj = SetTranningData( Obj,TrainingData )
        Obj = SetTestData( Obj,TestData )
        Obj = SetOutputDimension(Obj,OutputDm)
        Obj = SetIteration(Obj,Itr)
        Obj = SVDTranning(Obj)
       
        Obj = SVDTest(Obj)
    end
    methods(Access = private)
         Obj = PCAEignvalueCalculate(Obj)
    end
    
end

