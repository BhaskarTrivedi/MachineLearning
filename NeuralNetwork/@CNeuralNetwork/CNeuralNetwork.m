classdef CNeuralNetwork
    %NEURALNETWORKCLASS Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        Layers
        PerceptronperLayes
        Rounds
        TranningFileData
        TestFileData
        Dimension
        PerceptronHValue
        PereptronDeltaValue
        Weight
        TotalPerceptron
        LearningRate
        ClassNumber
        ClassCount
        MaxNormalize
        TotalAccuracy
    end
   
    methods
        Obj = SetTranningData( Obj,TrainingData )
        Obj = SetTestData( Obj,TestData )
        Obj = SetLayers( Obj,layers )
        Obj = SetPerceptronPerLayers( Obj,unitlayers )
        Obj = SetRounds( Obj,unitlayers )
        Obj = NeuralNetworkTranning( Obj )
        Obj = Classification( Obj )
    end
    methods(Access = private)
        Obj = Initialize(Obj)
        Obj = CalculateActivationFunc(Obj,TranningData);
        Obj = BackPropagation(Obj,TranningData);
        Obj = CalCulateClassification(Obj,TestData,ObjID);
    end
    
end

