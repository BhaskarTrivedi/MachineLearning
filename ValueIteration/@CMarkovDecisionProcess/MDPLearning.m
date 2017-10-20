function Obj = MDPLearning( Obj )
%MDPLEARNING Summary of this function goes here
%   Detailed explanation goes here
    [Row Col] = size(Obj.EnvironmentFileData);
    Obj.UtilityMat = zeros([Row Col]);    

    for Inr = 1:Obj.Iteration
        Obj = Obj.UpdateUtility();
    end
  %  disp(Obj.UtilityMat)
    for RowIndex = 1:Row
        ChangeStr = '';
        for ColIndex = 1:Col
            if(ColIndex ~= Col)
                UtilityDisp = sprintf('%6.3f,',Obj.UtilityMat(RowIndex,ColIndex));
            else
                UtilityDisp = sprintf('%6.3f',Obj.UtilityMat(RowIndex,ColIndex));
            end
            
            ChangeStr =strcat(ChangeStr,UtilityDisp);
        end
        disp(ChangeStr);
    end
end

