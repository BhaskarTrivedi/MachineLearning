classdef CMarkovDecisionProcess
    %CMARKOVDECISIONPROCESS Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        EnvironmentFileData
        Iteration
        NonTerminalReward
        Gamma
        UtilityMat
        UtilityMatNew
    end
    
    methods
        Obj = SetEnvironmentData( Obj,EnvironmentData )
        Obj = SetIteration(Obj,Itr)
        Obj = SetNonTerminalReward(Obj,Ntr)
        Obj = SetGamma(Obj,Gm)
        Obj = MDPLearning(Obj)
    end
    
    methods(Access = private)
         Obj = UpdateUtility(Obj)
         RightUtility = MoveRight(Obj,CurrentRow,CurrentCol)
         LeftUtility = MoveLeft(Obj,CurrentRow,CurrentCol)
         UpUtility = MoveUp(Obj,CurrentRow,CurrentCol)
         DownUtility = MoveDown(Obj,CurrentRow,CurrentCol)
    end
    
end

