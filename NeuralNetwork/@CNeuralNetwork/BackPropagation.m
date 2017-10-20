function Obj = BackPropagation( Obj,TranningData )
%BACKPROPAGATION Summary of this function goes here
%   Detailed explanation goes here
    [Rows,Cols] = size(TranningData);
 %   disp('BackPropagation');
    GivenClass = TranningData(1,Cols);
    LowerOutputIndex = Obj.Dimension + (Obj.Layers - 2)*Obj.PerceptronperLayes + 1;
    CurrentOutputIndex = LowerOutputIndex;
    InputToOutputLayerHigherIndex = LowerOutputIndex - 1;
  %  InputOutputLowerIndex = 0;
    if ( 2 == Obj.Layers)
        InputToOutputLayerLowerIndex = 1;
    else
        InputToOutputLayerLowerIndex = Obj.Dimension + (Obj.Layers - 3)*Obj.PerceptronperLayes + 1;
    end
    
    %Updating OutputLayers
    for OutputLayerIndex = 1 : Obj.ClassCount
        if( GivenClass == OutputLayerIndex - 1)
            Tvalue = 1;
        else
            Tvalue = 0;
        end
        Obj.PereptronDeltaValue(1,CurrentOutputIndex) = (Obj.PerceptronHValue(1,CurrentOutputIndex) - Tvalue) * Obj.PerceptronHValue(1,CurrentOutputIndex) * (1 - Obj.PerceptronHValue(1,CurrentOutputIndex));
        %disp(Obj.PereptronDeltaValue(1,CurrentOutputIndex));
        WeightIndex = 2;
        for InputIndex = InputToOutputLayerLowerIndex : InputToOutputLayerHigherIndex
    %        disp(Obj.Weight(CurrentOutputIndex,WeightIndex));
            Obj.Weight(CurrentOutputIndex,WeightIndex) = Obj.Weight(CurrentOutputIndex,WeightIndex) - Obj.LearningRate * Obj.PereptronDeltaValue(1,CurrentOutputIndex) * Obj.PerceptronHValue(1,InputIndex);
      %      disp(InputIndex);
      %      disp(Obj.Weight(CurrentOutputIndex,WeightIndex));
      %      disp(Obj.PerceptronHValue(1,InputIndex));
      %      disp(Obj.LearningRate);
            WeightIndex = WeightIndex + 1;
        end
        Obj.Weight(CurrentOutputIndex,1) = Obj.Weight(CurrentOutputIndex,1) - Obj.LearningRate * Obj.PereptronDeltaValue(1,CurrentOutputIndex);
        CurrentOutputIndex = 1 + CurrentOutputIndex;
    end
  
    if(2 <  Obj.Layers)
        %Traversing Layer for hidden layers
        for LayerIndex = Obj.Layers - 1 : -1 : 2
            PerceptronLowerIndex = ( Obj.Dimension + ( LayerIndex - 2)*Obj.PerceptronperLayes ) + 1;
            PerceptronHigherIndex = ( Obj.Dimension + ( LayerIndex - 1)*Obj.PerceptronperLayes );
            HigherLevelLowerIndex = PerceptronLowerIndex + 1;
            HigherLevelHigherIndex = 0;
            InputToHiddenLayerHigherIndex = PerceptronLowerIndex - 1;
            if( 2 == LayerIndex)
                InputToHiddenLayerLowerigherIndex = 1;
            else
                InputToHiddenLayerLowerigherIndex = (InputToHiddenLayerHigherIndex - Obj.PerceptronperLayes) + 1;
            end
            
            if( LayerIndex == (Obj.Layers - 1) )
                HigherLevelHigherIndex = PerceptronHigherIndex + Obj.ClassCount;
            else
                HigherLevelHigherIndex = PerceptronHigherIndex + Obj.PerceptronperLayes;
            end
            HeigherLevelWeightIndex = 2;
            for PerceptronIndex = PerceptronLowerIndex : PerceptronHigherIndex
                TempDelta = 0;
                
                %Calculating Delta for Hidden Layer
                for HigherIndex = HigherLevelLowerIndex : HigherLevelHigherIndex
                    TempDelta = TempDelta + Obj.PereptronDeltaValue(1,HigherIndex) * Obj.Weight(HigherIndex,HeigherLevelWeightIndex);
                end
                Obj.PereptronDeltaValue(1,PerceptronIndex)  = TempDelta * Obj.PerceptronHValue(1,PerceptronIndex) * (1 - Obj.PerceptronHValue(1,PerceptronIndex));
                HeigherLevelWeightIndex = 1 + HeigherLevelWeightIndex;
                
                %Updating weight for hidden layer
                HiddenLayerWeightIndex = 2;
                for InputHiddenIndex = InputToHiddenLayerLowerigherIndex : InputToHiddenLayerHigherIndex
                    Obj.Weight(PerceptronIndex,HiddenLayerWeightIndex) = Obj.Weight(PerceptronIndex,HiddenLayerWeightIndex) - Obj.LearningRate * Obj.PereptronDeltaValue(1,PerceptronIndex) * Obj.PerceptronHValue(1,InputHiddenIndex);
                    HiddenLayerWeightIndex = 1 + HiddenLayerWeightIndex;
                    
                    %{
                    disp('Perceptron Number');
                    disp(PerceptronIndex);
                    disp(Obj.PerceptronHValue(1,InputHiddenIndex));
                    disp(Obj.Weight(PerceptronIndex,HiddenLayerWeightIndex));
                    %}
                end
                Obj.Weight(PerceptronIndex,1) = Obj.Weight(PerceptronIndex,1) - Obj.LearningRate * Obj.PereptronDeltaValue(1,PerceptronIndex);
            end
        end
    end
    
end

