function Obj = CalculateAccuracy( Obj,TestObjectID,TestClassLevel,DistMat )
%CALCULATEACCURACY Summary of this function goes here
%   Detailed explanation goes here
    PredictedClass = 0;
    SortedDistance = sortrows(DistMat); % sort according to 1st column that is distance
%    disp(Test);
%    disp(SortedDistance)
    [DistanceRow DistanceCol ] = size(SortedDistance);
        SameDistanceCount = 0;
        for SameDistanceIndex = 1:DistanceRow
            if(SortedDistance(SameDistanceIndex,1) == SortedDistance(1,1))
                SameDistanceCount = SameDistanceCount + 1;
            else
                break;
            end
        end
        UniqueClass = unique(SortedDistance(1:SameDistanceCount,2));
        Accuracy = 0;
        PredictedClass = UniqueClass(1,1);
        [uniqueClassRow UniqueClassCol ] = size(UniqueClass);
        for RowIndex = 1:uniqueClassRow
            if(UniqueClass(RowIndex,1) == TestClassLevel)
                Accuracy = 1/uniqueClassRow;
                PredictedClass = UniqueClass(RowIndex,1);
                break;
            end
        end
        DisplayAccuracy = sprintf('ID=%5d, predicted=%3d, true=%3d, accuracy=%4.2f, distance = %.2f',TestObjectID, PredictedClass, TestClassLevel, Accuracy,SortedDistance(1,1));
        disp(DisplayAccuracy);
        Obj.ClassificationAccuracy = Obj.ClassificationAccuracy + Accuracy;
end

