function Obj = CalculateRMatrix( Obj )
%CALCULATERMATRIX Summary of this function goes here
%   Detailed explanation goes here
    [rows,cols] = size(Obj.ActivationOutput);
    for row = 1:rows
        for col = 1:rows
            if (row == col)
                if(Obj.ActivationOutput(row,1) == 1)
                    Obj.ActivationOutput(row,1) = 0.0001;
                elseif(Obj.ActivationOutput(row,1) == 0.9999)
                    Obj.ActivationOutput(row,1) = 0.0001;
                end
                Obj.RMatrix(row,col) = Obj.ActivationOutput(row,1) * ( 1 - Obj.ActivationOutput(row,1));
            end
        end
    end
 %   disp(Obj.RMatrix)
end

