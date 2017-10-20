function Obj = LogRegression( Obj )
%LOGREGRESSION Summary of this function goes here
%   Detailed explanation goes here
    [rows,cols] = size(Obj.TranningFileData); 
    Obj.ActivationOutput = zeros(rows,1);
    Obj.RMatrix = zeros(rows,rows);
    Obj = InitializeWeight(Obj);
    Obj = InitializeError(Obj);
    Obj = InitializeClassOutput(Obj);
    Obj = InitializePhiMatrix( Obj );
 %   count = 1;
    while 1
        Obj = CalculateActivationOutput(Obj);
        Obj = CalculateRMatrix(Obj);
        Obj = UpdateWeight(Obj);
        Obj = CalculateAbsWeight(Obj);
        Obj = CalculateAbsError(Obj);
      %  disp(count);
      %  count = count +1;
      %  if( (0.001 < Obj.AbsoluteWeight) || (0.001 < Obj.AbsError))
        weightflag = 0.001 < Obj.AbsoluteWeight;
        ErrorFlag = 0.001 < Obj.AbsError;
        if( weightflag || ErrorFlag)
            Obj.WeightOld = Obj.WeightNew;
            Obj.ErrorOld = Obj.ErrorNew;
        else
            break;
        end
    end
    [rows,cols] = size(Obj.WeightNew);
    %disp(Obj.WeightNew);
    for row = 1:rows
     %   disp(Obj.WeightNew(row,1))
        Dis = sprintf('W%d=%.4f',row,Obj.WeightNew(row,1));
        disp(Dis);
    end
    
    Obj = LogisticsClassification(Obj);

end

