function Obj = NeuralNetworkTranning( Obj )
%NEURALNETWORKTRANNING Summary of this function goes here
%   Detailed explanation goes here

%    disp(Obj.Layers);
%    disp(Obj.UnitsperLayes);
%    disp(Obj.Rounds);
    
    Obj = Initialize(Obj);

    [Rows,Cols] = size(Obj.TranningFileData);
    
    
    for index = 1:Obj.Rounds
        for row = 1: Rows
            TranningData = Obj.TranningFileData(row,:);
            Obj = CalculateActivationFunc(Obj,TranningData);
            Obj = BackPropagation(Obj,TranningData);
            
       %     Obj = CalculateActivationFunc(Obj,TranningData);
        end
        Obj.LearningRate = 0.98 * Obj.LearningRate;
     %   disp(index);
    end
    

    for index = 1 : Obj.TotalPerceptron
%        disp(index);
%        disp(Obj.PerceptronHValue(1,index));
%        disp(Obj.Weight(index,:))
    end
    
 %   disp(size(Obj.PerceptronHValue));

end

