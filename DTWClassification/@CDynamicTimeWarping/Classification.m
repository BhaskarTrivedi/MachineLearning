function Obj = Classification( Obj )
%CLASSIFICATION Summary of this function goes here
%   Detailed explanation goes here
    Obj.ClassificationAccuracy = 0;
    TotalTestData = numel(Obj.TestFileData);
    TotalTrannigData = numel(Obj.TranningFileData);
    
    for TestDataIndex  = 1:TotalTestData
   %     [ TestDataRow,TestDataCol ] = size(Obj.TestFileData(TestDataIndex).dominant_hand_trajectory);
        Obj.ClassDistance = [];
        for TranningDataIndex = 1:TotalTrannigData
            OptimalCost = Obj.CostMat(Obj.TranningFileData(TranningDataIndex).dominant_hand_trajectory,Obj.TestFileData(TestDataIndex).dominant_hand_trajectory);
            classLevel = Obj.TranningFileData(TranningDataIndex).class_label;
            Obj.ClassDistance(end+1,:) = [OptimalCost classLevel];
            
         %   disp(Obj.TranningFileData(TranningDataIndex).class_label);
            %{
            [ TranningDataRow,TranningDataCol ] = size(Obj.TranningFileData(TranningDataIndex).dominant_hand_trajectory);
            CostMat(1:TranningDataRow,1:TestDataRow) = 0;
            CostMat(1,1) = Obj.EuclideanDistance(Obj.TranningFileData(TranningDataIndex).dominant_hand_trajectory(1,:),Obj.TestFileData(TestDataIndex).dominant_hand_trajectory(1,:));
    %        disp(CurrentCost);
      %      disp(Obj.TestFileData(TestDataIndex).dominant_hand_trajectory(1,:));

            for ColIndex = 2:TestDataRow
                currentCost = Obj.EuclideanDistance(Obj.TranningFileData(TranningDataIndex).dominant_hand_trajectory(1,:),Obj.TestFileData(TestDataIndex).dominant_hand_trajectory(ColIndex,:));
                CostMat(1,ColIndex) = CostMat(1,ColIndex-1) + currentCost;
            end
            for RowIndex = 2:TranningDataRow
                currentCost = Obj.EuclideanDistance(Obj.TranningFileData(TranningDataIndex).dominant_hand_trajectory(RowIndex,:),Obj.TestFileData(TestDataIndex).dominant_hand_trajectory(1,:));
                CostMat(RowIndex,1) = CostMat(RowIndex - 1,1) + currentCost;
            end
            for ColIndexFinal = 2:TestDataRow
                for RowIndexFinal = 2:TranningDataRow
                    currentCostFinal = Obj.EuclideanDistance(Obj.TranningFileData(TranningDataIndex).dominant_hand_trajectory(RowIndexFinal,:),Obj.TestFileData(TestDataIndex).dominant_hand_trajectory(ColIndexFinal,:));
                    NeighbourCost = [CostMat(RowIndexFinal-1,ColIndexFinal-1),CostMat(RowIndexFinal-1,ColIndexFinal),CostMat(RowIndexFinal,ColIndexFinal-1)];
                    MinCost = min(NeighbourCost) + currentCostFinal;
                    CostMat(RowIndexFinal,ColIndexFinal) = MinCost;
                end
            end
            %}
        %    disp(CostMat);
        end     
        Obj = Obj.CalculateAccuracy(Obj.TestFileData(TestDataIndex).object_ID,Obj.TestFileData(TestDataIndex).class_label,Obj.ClassDistance);
    end
    DispClassifiAcc = sprintf('classification accuracy=%6.4f\n', Obj.ClassificationAccuracy/TotalTestData);
    disp(DispClassifiAcc);

end

