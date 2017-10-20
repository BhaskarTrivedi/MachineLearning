function LeftUtility = MoveLeft( Obj,CurrentRow,CurrentCol )
%MOVELEFT Summary of this function goes here
%   Detailed explanation goes here

    [Row Col] = size(Obj.EnvironmentFileData);
    %Moving Left with 0.8 probability
    if(CurrentCol == 1 || (strcmp(Obj.EnvironmentFileData(CurrentRow,CurrentCol - 1),'X') ))
        Data1 = 0.8 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );
    else
        Data1 = 0.8 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol - 1) );
    end
    
    %Moving Up with 0.1 probability
    if(CurrentRow == 1 || strcmp(Obj.EnvironmentFileData(CurrentRow-1,CurrentCol),'X'))
        Data2 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );
    else
        Data2 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow-1,CurrentCol) );
    end

    %Moving Down with 0.1 probability
    if(CurrentRow == Row || strcmp(Obj.EnvironmentFileData(CurrentRow+1,CurrentCol),'X') )
        Data3 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );
    else
        Data3 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow+1,CurrentCol) );
    end

    LeftUtility = Data1 + Data2 + Data3;

end

