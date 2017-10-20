function OptCost = CostMat( Obj,TranningDataPath,TestDataPath )
%COSTMAT Summary of this function goes here
%   Detailed explanation goes here
    
    [ TestDataRow,TestDataCol ] = size(TestDataPath);
    [ TranningDataRow,TranningDataCol ] = size(TranningDataPath);
        CostMat(1:TranningDataRow,1:TestDataRow) = 0;
        CostMat(1,1) = Obj.EuclideanDistance(TranningDataPath(1,:),TestDataPath(1,:));
    %        disp(CurrentCost);
      %      disp(Obj.TestFileData(TestDataIndex).dominant_hand_trajectory(1,:));

        for ColIndex = 2:TestDataRow
            currentCost = Obj.EuclideanDistance(TranningDataPath(1,:),TestDataPath(ColIndex,:));
            CostMat(1,ColIndex) = CostMat(1,ColIndex-1) + currentCost;
        end
        for RowIndex = 2:TranningDataRow
            currentCost = Obj.EuclideanDistance(TranningDataPath(RowIndex,:),TestDataPath(1,:));
            CostMat(RowIndex,1) = CostMat(RowIndex - 1,1) + currentCost;
        end
        for ColIndexFinal = 2:TestDataRow
            for RowIndexFinal = 2:TranningDataRow
                currentCostFinal = Obj.EuclideanDistance(TranningDataPath(RowIndexFinal,:),TestDataPath(ColIndexFinal,:));
                NeighbourCost = [CostMat(RowIndexFinal-1,ColIndexFinal-1),CostMat(RowIndexFinal-1,ColIndexFinal),CostMat(RowIndexFinal,ColIndexFinal-1)];
                MinCost = min(NeighbourCost) + currentCostFinal;
                CostMat(RowIndexFinal,ColIndexFinal) = MinCost;
            end      
        end
  %  disp(TestDataRow);
 %   disp(TranningDataRow);
 %   disp(CostMat);
    OptCost = CostMat(end,end);
end

