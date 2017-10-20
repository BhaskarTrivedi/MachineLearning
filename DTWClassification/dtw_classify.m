function Y = dtw_classify( TranningFile,TestFile )
%DTW_CLASSIFY Summary of this function goes here
%   Detailed explanation goes here

%TranningData = struct('object_ID',{},'class_label',{},'sign_meaning',{},'dominant_hand_trajectory',{});
%TranningData(1).dominant_hand_trajectory = magic(5);
%disp(TranningData(1).dominant_hand_trajectory);

FR = FileRead;
FR = ReadTranningFile(FR,TranningFile);
FR = ReadTestFile(FR,TestFile);

TranningFileData = GetTranningData(FR);
TestFileData = GetTestData(FR);

DynamicTimeWarpingObj = CDynamicTimeWarping;
DynamicTimeWarpingObj = DynamicTimeWarpingObj.SetTranningData(TranningFileData);
DynamicTimeWarpingObj = DynamicTimeWarpingObj.SetTestData(TestFileData);
DynamicTimeWarpingObj = DynamicTimeWarpingObj.Classification();

%{
TotalTrannigData = numel(TranningFileData);
TotalTestData = numel(TestFileData);


for Index = 1:TotalTrannigData
   disp((TranningFileData(Index).object_ID));
    disp((TranningFileData(Index).class_label));
    disp((TranningFileData(Index).sign_meaning));
    disp((TranningFileData(Index).dominant_hand_trajectory));
end

for TestIndex = 1:TotalTestData
   disp((TestFileData(TestIndex).object_ID));
    disp((TestFileData(TestIndex).class_label));
    disp((TestFileData(TestIndex).sign_meaning));
    disp((TestFileData(TestIndex).dominant_hand_trajectory));
end
%}
%disp((TranningFileData(1).dominant_hand_trajectory));
end

