function Obj = InitializePhiMatrix( Obj )
%INITIALIZEPHIMATRIX Summary of this function goes here
%   Detailed explanation goes here
    [rows,cols] = size(Obj.TranningFileData); 
    for row = 1:rows
        PhiCol = 1;
        for col = 1:cols
            if(1==col)
                Obj.PhiMatrix(row,PhiCol) = 1;
                PhiCol = PhiCol + 1;
            end
         %   else
                if(col ~= cols)
                    Obj.PhiMatrix(row,PhiCol) = Obj.TranningFileData(row,col);
                    PhiCol = PhiCol + 1;
                    if(2 == Obj.Degree)
                        Obj.PhiMatrix(row,PhiCol) = Obj.TranningFileData(row,col) * Obj.TranningFileData(row,col);
                        PhiCol = PhiCol + 1;
                    end 
                end           
            %end
        end
    end
  %  disp(Obj.PhiMatrix);
end

