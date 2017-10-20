function Obj  = Classification( Obj )
%CLASSIFICATION Summary of this function goes here
%   Detailed explanation goes here
    [TestRow,TestCol] = size(Obj.NormTestFileData);
    Obj.ClassField = Obj.TranningFileData(:,end);
    TotalAccurate = 0;

    for testRow = 1: TestRow
        CurrentRow = Obj.NormTestFileData(testRow,:);
        DistanceSub = Obj.NormTranningFileData - CurrentRow;
        SquareDistance = DistanceSub.^2;
        SumDistance = sum(SquareDistance,2);
        SquareRootDistance = SumDistance.^.5;
        SquareRootDistance(:,end+1) = Obj.ClassField;
        SortedDistance = sortrows(SquareRootDistance);
        KNeighbour = SortedDistance(1:Obj.NearestNeighbourCount,:);
        KNeighbourClass = KNeighbour(:,end);
        NearestUniqueClass=unique(KNeighbourClass); 
        NearestUniqueClassFrequency = tabulate(KNeighbourClass );
        SortedDist = sortrows(NearestUniqueClassFrequency,-2);
        if(SortedDist(1,1) == Obj.TestFileData(testRow,end))
            Accuracy = 1;
            TotalAccurate = TotalAccurate + 1;
        else
            Accuracy = 0;
        end
        DisplayAccuracy = sprintf('ID=%5d, predicted=%3d, true=%3d, accuracy=%4.2f',testRow, SortedDist(1,1), Obj.TestFileData(testRow,end), Accuracy);
        disp(DisplayAccuracy);
    end
    DispClassifiAcc = sprintf('classification accuracy=%6.4f\n', TotalAccurate/TestRow);
    disp(DispClassifiAcc);
end

