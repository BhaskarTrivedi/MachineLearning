classdef CPCAPower
    %CPCAPOWER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        TranningFileData
        TestFileData
        TrData %withoutClass
        TsData %withoutClass
        OutputDimension
        Iteration
        Dimension
        EgnVec
    end
    
    methods
        Obj = SetTranningData( Obj,TrainingData )
        Obj = SetTestData( Obj,TestData )
        Obj = SetOutputDimension(Obj,OutputDm)
        Obj = SetIteration(Obj,Itr)
        Obj = PCATranning(Obj)
        Obj = PCATest(Obj)
    end
    methods(Access = private)
        
    end
    
end

