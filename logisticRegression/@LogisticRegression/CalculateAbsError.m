function Obj = CalculateAbsError( Obj )
%CALCULATEABSERROR Summary of this function goes here
%   Detailed explanation goes here
    ErrorDiff = Obj.ErrorNew - Obj.ErrorOld;
    Obj.AbsError = abs(sum(ErrorDiff));
  %  disp(Obj.AbsError);
end

