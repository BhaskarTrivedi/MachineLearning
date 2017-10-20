function DownUtility = MoveDown( Obj,CurrentRow,CurrentCol )
%MOVEDOWN Summary of this function goes here
%   Detailed explanation goes here
[Row Col] = size(Obj.EnvironmentFileData);
    
 %  disp(CurrentRow);
 %   disp(CurrentCol);
 %Going to left side with probability 0.1
    if(CurrentCol == 1 || (strcmp(Obj.EnvironmentFileData(CurrentRow,CurrentCol - 1),'X') ))
        Data1 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );    
    else
        Data1 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol - 1) );
    end
    
    %Going  Down  with probability 0.8
    if(CurrentRow == Row || strcmp(Obj.EnvironmentFileData(CurrentRow+1,CurrentCol),'X'))
        Data2 = 0.8 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );
    else
        Data2 = 0.8 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow+1,CurrentCol) );
    end
  
  %Going  Right  with probability 0.1  
    if(CurrentCol == Col || (strcmp(Obj.EnvironmentFileData(CurrentRow,CurrentCol + 1),'X') ))
        Data3 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol) );      
    else
        Data3 = 0.1 * ( Obj.NonTerminalReward + Obj.Gamma * Obj.UtilityMat(CurrentRow,CurrentCol + 1) );
    end
    DownUtility = Data1 + Data2 + Data3;



end

