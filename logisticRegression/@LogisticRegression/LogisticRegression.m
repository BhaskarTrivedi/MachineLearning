classdef LogisticRegression < matlab.mixin.CustomDisplay
    %UNTITLED5 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Access = private)
        Degree
        TranningFileData
        TestFileData
        ClassOutput
        WeightOld
        WeightNew
        ErrorOld
        ErrorNew
        ActivationOutput
        Dimension
        PhiMatrix
        RMatrix
        AbsoluteWeight
        AbsError
    end
    methods
         Obj = SetDegree( Obj,Deg ) 
         Obj = SetTranningData( Obj,TrainingData )
         Obj = SetTestData( Obj,TestData )
         Obj = LogRegression(Obj)
    end
    methods(Access = private)
        
        Obj = InitializePhiMatrix(Obj)
        Obj = CalculateActivationOutput(Obj)
        Obj = CalculateRMatrix(Obj)
        Obj = UpdateWeight(Obj)
        Obj = CalculateAbsWeight(Obj)
        Obj = CalculateAbsError(Obj)
        Obj = LogisticsClassification(Obj)
        
        function Obj = InitializeWeight(Obj)
            
            MatSize = size(Obj.TranningFileData);
            Obj.Dimension = MatSize(2) - 1;
            NoofWeight = Obj.Degree * Obj.Dimension +1;
            Obj.WeightOld = zeros(NoofWeight,1);
            Obj.WeightNew = zeros(NoofWeight,1);
        end
        
        function Obj = InitializeError(Obj)
            MatSize = size(Obj.TranningFileData);
            Obj.Dimension = MatSize(2) - 1;
            NoofWeight = Obj.Degree * Obj.Dimension +1;
            Obj.ErrorOld = zeros(NoofWeight,1);
            Obj.ErrorNew = zeros(NoofWeight,1);
        end
        
        
        function Obj = InitializeClassOutput(Obj)
            [rows,cols] = size(Obj.TranningFileData);
            for row = 1:rows
                for col = 1:cols
                    if(col == cols)
                        if( 1 == Obj.TranningFileData(row,col))
                            Obj.ClassOutput(row,1) = 1;
                        else
                            Obj.ClassOutput(row,1) = 0;
                        end
                    else  
                    end
                end
            end
         %   disp(size(Obj.ClassOutput))
        end
    end
    
end

