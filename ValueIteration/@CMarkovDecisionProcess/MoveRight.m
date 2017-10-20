function RightUtility = MoveRight( Obj,CurrentRow,CurrentCol )
%MOVERIGHT Summary of this function goes here
%   Detailed explanation goes here
    [Row Col] = size(Obj.EnvironmentFileData);
    
    %Moving Right with 0.8 Probability
    if(CurrentCol == Col || (strcmp(Obj.EnvironmentFileData(CurrentRow,CurrentCol + 1),'X') ))
        Data1 = 0.8 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );       
    else
        Data1 = 0.8 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol + 1) );
    end
    
    %Moving Up with 0.1 Probability
    if(CurrentRow == 1 || strcmp(Obj.EnvironmentFileData(CurrentRow-1,CurrentCol),'X'))
        Data2 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );
    else
        Data2 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow-1,CurrentCol) );
    end
    
    %Moving Down with 0.1 Probability   
    if(CurrentRow == Row || strcmp(Obj.EnvironmentFileData(CurrentRow+1,CurrentCol),'X') )
        Data3 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );
    else
        Data3 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow+1,CurrentCol) );
    end
    RightUtility = Data1 + Data2 + Data3;


end

