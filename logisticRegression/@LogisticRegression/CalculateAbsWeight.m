function Obj = CalculateAbsWeight( Obj )
%CALCULATEABSWEIGHT Summary of this function goes here
%   Detailed explanation goes here
  %  [rows,cols] = size(Obj.WeightOld);
    WeightDiff = Obj.WeightNew - Obj.WeightOld;
    Obj.AbsoluteWeight = abs(sum(WeightDiff));
 %   disp('absweight');
 %   disp(Obj.AbsoluteWeight);
end

