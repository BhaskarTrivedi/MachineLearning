function Obj = UpdateUtility( Obj )
%UPDATEUTILITY Summary of this function goes here
%   Detailed explanation goes here
    [Row Col] = size(Obj.EnvironmentFileData);
    Obj.UtilityMatNew = Obj.UtilityMat;
    CurrentValue = [];
    for RowIndex = 1:Row
        for ColIndex = 1:Col
          %  disp(RowIndex);
          %  disp(ColIndex);
            if(strcmp(Obj.EnvironmentFileData(RowIndex,ColIndex),'X'))
                continue;
            end
            if(~strcmp(Obj.EnvironmentFileData(RowIndex,ColIndex),'X') && ~strcmp(Obj.EnvironmentFileData(RowIndex,ColIndex),'.'))
                Obj.UtilityMatNew(RowIndex,ColIndex) = str2double(Obj.EnvironmentFileData(RowIndex,ColIndex));
                continue;
            end
            
            %Moving Right
           % Obj.UtilityMatNew(RowIndex,ColIndex) = Obj.MoveRight(RowIndex,ColIndex);
            CurrentValue(1,1)  = Obj.MoveRight(RowIndex,ColIndex);
            %Move Left
            CurrentValue(1,2)  = Obj.MoveLeft( RowIndex,ColIndex );
            %Move Up
            CurrentValue(1,3) = Obj.MoveUp( RowIndex,ColIndex );
            %Move Down
            CurrentValue(1,4) = Obj.MoveDown( RowIndex,ColIndex );           
            Obj.UtilityMatNew(RowIndex,ColIndex) = max(CurrentValue);
        %    disp(CurrentValue);
        end
    end
    Obj.UtilityMat = Obj.UtilityMatNew;
 %   disp(Obj.UtilityMat)

end

