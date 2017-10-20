function Obj = CalculateActivationOutput( Obj )
%CALCULATEACTIVATIONOUTPUT Summary of this function goes here
%   Detailed explanation goes here
    [rows,cols] = size(Obj.PhiMatrix);
    
    TransWeight = Obj.WeightOld.';
    for row = 1:rows
        localPhi = zeros(cols,1);
        for col = 1:cols
            localPhi(col,1) = Obj.PhiMatrix(row,col);
        end
        
        WgtPhiMul = TransWeight * localPhi;
        express = 1 + exp( -1 * WgtPhiMul);
        Obj.ActivationOutput(row,1) = 1 / express;
    end
  %  disp(size(TransWeight))
 %   disp(size(Obj.PhiMatrix))
%   disp(size(Obj.ActivationOutput))
 %  disp(Obj.ActivationOutput)
end

