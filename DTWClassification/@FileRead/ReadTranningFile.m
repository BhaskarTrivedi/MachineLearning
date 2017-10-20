function Obj = ReadTranningFile( Obj,TranningFileName )
%READTRANNINGFILE Summary of this function goes here
%   Detailed explanation goes here

 %   Obj.TranningFileData(1).dominant_hand_trajectory = magic(5);
 %   Obj.TranningFileData(2).dominant_hand_trajectory = magic(5);
 

    TranningIndex = 0;
    ReadPoint = 0;
    
    FileId = fopen(TranningFileName);
    LineData = fgetl(FileId);
    while ischar(LineData)
        SubStr = '';
        if(length(LineData) > 4)
            SubStr = LineData(1:4);
        end
        if(strcmp(SubStr,'obje'))
            TranningIndex = TranningIndex + 1;
            Obj.TranningFileData(TranningIndex).object_ID = str2double(LineData(12:length(LineData)));
        elseif(strcmp(SubStr,'clas'))
            Obj.TranningFileData(TranningIndex).class_label = str2double(LineData(14:length(LineData)));
        elseif(strcmp(SubStr,'sign'))
            Obj.TranningFileData(TranningIndex).sign_meaning = LineData(15:length(LineData));  
        elseif(strcmp(SubStr,'domi'))
            ReadPoint = 1;
            LineData = fgetl(FileId);
        elseif(strcmp(SubStr,'----'))
            ReadPoint = 0;
        end
        if(ReadPoint)
            [ponit1,point2] = strtok(LineData);
            ponit1Double = str2double(ponit1);
            point2Str = strtok(point2);
            point2Double = str2double(point2Str);
            Obj.TranningFileData(TranningIndex).dominant_hand_trajectory(end+1,:) = [ponit1Double,point2Double];
        end
        LineData = fgetl(FileId);
    end

    fclose(FileId);
end

