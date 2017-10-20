function Obj = ReadEnvironmentFile( Obj,EnvironmentFileName )
%READENVIRONMENTFILE Summary of this function goes here
%   Detailed explanation goes here
    FileId = fopen(EnvironmentFileName);
    LineData = fgetl(FileId);
    RowIndex = 1;
     Obj.EnvironmentFileData = {};
    while ischar(LineData)
        column = 1;
        [str1,str2] = strtok(LineData,',');
        Obj.EnvironmentFileData(RowIndex,column) = {str1};
        while(0 ~= length(str2))  
            column = column + 1;
            [str1,str2] = strtok(str2,',');
            Obj.EnvironmentFileData(RowIndex,column) = {str1};            
        end   
        LineData = fgetl(FileId);
        RowIndex = RowIndex + 1;
    end
    fclose(FileId);
end

