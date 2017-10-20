function Obj = SetTestData( Obj,TestFileData )
%SETTESTDATA Summary of this function goes here
%   Detailed explanation goes here
    Obj.TestFileData = TestFileData;
    %{
    TotalTrannigData = numel(Obj.TestFileData);
    for Index = 1:TotalTrannigData
        disp((Obj.TestFileData(Index).object_ID));
        disp((Obj.TestFileData(Index).class_label));
        disp((Obj.TestFileData(Index).sign_meaning));
        disp((Obj.TestFileData(Index).dominant_hand_trajectory));
    end
    %}
end

