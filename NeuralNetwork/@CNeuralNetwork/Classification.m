function Obj = Classification( Obj )
%CLASSIFICATION Summary of this function goes here
%   Detailed explanation goes here
    [Rows,Cols] = size(Obj.TestFileData);
 %   disp(Rows);
    
    for TestDataIndex = 1 : Rows
        TestData = Obj.TestFileData(TestDataIndex,:);
        Obj = CalCulateClassification(Obj,TestData,TestDataIndex-1);
    end
 %   disp('Classification');
    Dis = sprintf('classification accuracy=%.4f',Obj.TotalAccuracy/Rows);
    disp(Dis);
end

