function Obj = SetTranningData( Obj,TrainingData )
%SETTRANNINGDATA Summary of this function goes here
%   Detailed explanation goes here
    Obj.TranningFileData = TrainingData;
    %{
    TotalTrannigData = numel(Obj.TranningFileData);
    for Index = 1:TotalTrannigData
        disp((Obj.TranningFileData(Index).object_ID));
        disp((Obj.TranningFileData(Index).class_label));
        disp((Obj.TranningFileData(Index).sign_meaning));
        disp((Obj.TranningFileData(Index).dominant_hand_trajectory));
    end
    %}
end

