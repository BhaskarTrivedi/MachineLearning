function Obj = Initialize( Obj )
%INITIALIZE Summary of this function goes here
%   Detailed explanation goes here
    [Rows,Cols] = size(Obj.TranningFileData);
    Class = Obj.TranningFileData(:,Cols);
    Obj.ClassNumber = unique(Class);
    Obj.MaxNormalize = 0;
    Obj.TotalAccuracy = 0;
    for row = 1: Rows
        for col = 1 :Cols-1
            if( Obj.MaxNormalize < Obj.TranningFileData(row,col))
                Obj.MaxNormalize = Obj.TranningFileData(row,col);
            end            
        end
    end
  %  disp(Obj.ClassNumber);
    Obj.Dimension = Cols - 1;
  %  disp(size(Obj.ClassNumber));
  %  disp(Obj.Dimension);
    [ClassCnt,ClassCol] = size(Obj.ClassNumber); 
    Obj.ClassCount = ClassCnt;
    if( Obj.Layers > 2)
        Obj.TotalPerceptron = Obj.Dimension + Obj.PerceptronperLayes * (Obj.Layers-2) + Obj.ClassCount;
    else
        Obj.TotalPerceptron = Obj.Dimension + Obj.ClassCount;
        Obj.PerceptronperLayes = Obj.Dimension;
    end
    if(Obj.Dimension > Obj.PerceptronperLayes)
        WeightEachPerceptron = Obj.Dimension + 1;
    else
        WeightEachPerceptron = Obj.PerceptronperLayes + 1;
    end
    Obj.LearningRate = 1;
    Obj.PerceptronHValue = zeros(1,Obj.TotalPerceptron);
    Obj.PereptronDeltaValue  = zeros(1,Obj.TotalPerceptron);
    Obj.Weight = zeros(Obj.TotalPerceptron,WeightEachPerceptron);
    Obj.Weight(:) = 0.05;
%    disp(size(Obj.Weight));
    
end

