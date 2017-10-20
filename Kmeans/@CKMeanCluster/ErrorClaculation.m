function Obj = ErrorClaculation( Obj )
%ERRORCLACULATION Summary of this function goes here
%   Detailed explanation goes here
    [Row Col] = size(Obj.TestDataWOClass);
    Obj.ClusterMean = grpstats( Obj.TestDataWOClass(:,1:end-1),Obj.TestDataWOClass(:,end) );
    
    ClusterMeanIndex = Obj.TestDataWOClass(:,end);
    DataIndexRow = linspace(1,Row,Row);
    DataIndex = DataIndexRow.';
 %   disp(ClusterMeanIndex)
 %   disp(DataIndex);
    DifferenceMat = Obj.ClusterMean(ClusterMeanIndex,:) - Obj.TestDataWOClass(DataIndex,1:end-1);  
%    disp(DifferenceMat);
    SquareDifferenceMat = DifferenceMat.^2;
%    disp(SquareDifferenceMat);
    SumDistance = sum(SquareDifferenceMat,2);
    SquareRootDistance = SumDistance.^.5;
 %   disp(SquareRootDistance);
    Obj.ErrorValue = sum(SquareRootDistance);


end

