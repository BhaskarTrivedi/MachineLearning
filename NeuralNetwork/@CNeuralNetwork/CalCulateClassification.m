function Obj = CalCulateClassification( Obj,TestData,ObjID )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

 %   disp('CalClass');
    [Rows,Cols] = size(TestData);
    ActualClass = TestData(1,Cols);
    PredictedClass = 0;
    HighestProbability = -1;
    PredictedClassCount = 0;
    
    

    Obj = CalculateActivationFunc(Obj,TestData);
    OutputPerceptronLowerIndex = Obj.Dimension + (Obj.Layers - 2)*Obj.PerceptronperLayes + 1;
 %   disp(OutputPerceptronLowerIndex);
    OutputPerceptronHigherIndex =  OutputPerceptronLowerIndex + Obj.ClassCount - 1;
 %   disp(OutputPerceptronHigherIndex);
    CurrentClass = Obj.ClassNumber(1,1);
    for Index = OutputPerceptronLowerIndex : OutputPerceptronHigherIndex
        if( HighestProbability < Obj.PerceptronHValue(1,Index))
            PredictedClass = CurrentClass;
            HighestProbability = Obj.PerceptronHValue(1,Index);
            if(PredictedClass == ActualClass)
                PredictedClassCount = 1;
            end
            
        elseif(HighestProbability == Obj.PerceptronHValue(1,Index))
            if(ActualClass == CurrentClass)
                PredictedClass = ActualClass;
            end
            PredictedClassCount = 1 + PredictedClassCount;
        end
        CurrentClass = 1 + CurrentClass;
    end
    if(0==PredictedClassCount)
        Accuracy = 0;
    else
        Accuracy = 1 / PredictedClassCount;
    end
    
    Obj.TotalAccuracy = Obj.TotalAccuracy + Accuracy;
    
    ObjectDis = sprintf('ID=%5d, predicted=%3d, true=%3d, accuracy=%4.2f',ObjID,PredictedClass,ActualClass,Accuracy);
    disp(ObjectDis);

    for index = 1 : Obj.TotalPerceptron
   %     disp(Obj.PerceptronHValue(1,index));
      %  disp(Obj.Weight(index,:))
    end

end

