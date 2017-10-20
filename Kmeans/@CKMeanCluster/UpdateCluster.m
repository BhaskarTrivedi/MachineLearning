function Obj = UpdateCluster( Obj )
%UPDATECLUSTER Summary of this function goes here
%   Detailed explanation goes here
    
    [DataRow DataCol] = size(Obj.TestDataWOClass);
    for DataRowIndex = 1:DataRow
        DiffMat = Obj.TestDataWOClass(DataRowIndex,1:end-1) - Obj.ClusterMean;
        SquareDifferenceMat = DiffMat.^2;
        SumDistance = sum(SquareDifferenceMat,2);
        SquareRootDistance = SumDistance.^.5;
        [MinValue MinIndence] = min(SquareRootDistance);
        Obj.TestDataWOClass(DataRowIndex,end) = MinIndence;
    end
    
end

