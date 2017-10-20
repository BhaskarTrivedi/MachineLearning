function Obj = CalculateActivationFunc( Obj,Data )
%CALCULATEACTIVATIONFUNC Summary of this function goes here
%   Detailed explanation goes here
    InputPerceptron = 0;
    PerceptronCurrentLayer = 0;
    LowerInputLimit = 0;
    UpperInputLimit = 0;
    BaseFuncCal = 0;
    for AFIndex = 1 : Obj.Dimension
        Obj.PerceptronHValue(1,AFIndex) = Data(1,AFIndex)/Obj.MaxNormalize;
    end
    CurAFIndex = Obj.Dimension + 1;
%    if( Obj.Layers > 2)
        for LayerNum = 2:Obj.Layers
            if(LayerNum == Obj.Layers)
                PerceptronCurrentLayerCount = Obj.ClassCount;
            else
                PerceptronCurrentLayerCount = Obj.PerceptronperLayes;
            end
            if (LayerNum == 2)
                LowerInputLimit = 1;
                UpperInputLimit = Obj.Dimension + (LayerNum - 2)*Obj.PerceptronperLayes;
            else
                LowerInputLimit = Obj.Dimension + (LayerNum - 3)*Obj.PerceptronperLayes + 1;
                UpperInputLimit = Obj.Dimension + (LayerNum - 2)*Obj.PerceptronperLayes;
            end
   %        disp(LowerInputLimit);
    %        disp(UpperInputLimit);
            for PerceptronIndex = 1 : PerceptronCurrentLayerCount
                Weightindex = 2;
                BaseFuncCal = 0;
                for BaseFunIndex = LowerInputLimit : UpperInputLimit
         %           disp(BaseFunIndex);
         %           disp(size(Obj.PerceptronHValue));
                    BaseFuncCal = BaseFuncCal + Obj.Weight(CurAFIndex,Weightindex)* Obj.PerceptronHValue(1,BaseFunIndex);
                    Weightindex = Weightindex + 1;
                end
                BaseFuncCal = BaseFuncCal + Obj.Weight(CurAFIndex,1);
             %   disp('BaseFuncCal');
             %   disp(BaseFuncCal);
                expCal = 1 + exp(-1 * BaseFuncCal);
             %   disp(expCal);
                Obj.PerceptronHValue(1,CurAFIndex) = 1 / expCal;
                CurAFIndex = CurAFIndex + 1;
            end
        end
%    else
%    end
    
    
end

