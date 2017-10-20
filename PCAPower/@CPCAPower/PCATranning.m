function Obj = PCATranning( Obj )
%PCATRANNING Summary of this function goes here
%   Detailed explanation goes here
    Obj.TrData = Obj.TranningFileData(1:end,1:end-1); 
 %   disp(Obj.TrData);
    [Row,Col] = size(Obj.TrData); 
    for OutDm = 1:Obj.OutputDimension
        TempEgnVec = ones([Col,1]);
        CoveranceMat = cov(Obj.TrData);
        for Itr = 1:Obj.Iteration      
            EgnVecMul = CoveranceMat * TempEgnVec;
            TempEgnVec = EgnVecMul / norm(EgnVecMul);
        end
        if OutDm == 1
            Obj.EgnVec = TempEgnVec;
        else
            Obj.EgnVec(:,end+1) = TempEgnVec;
        end
        for row = 1:Row
            TemXValue = Obj.TrData(row,:);
            TemXValueTrans = TemXValue.';
            Temp = TemXValueTrans - TempEgnVec.' * TemXValueTrans * TempEgnVec;
            Obj.TrData(row,:) = Temp;
        end
    end
    [RowEign,ColEign] = size(Obj.EgnVec);
    
    for colEign = 1:ColEign
        Dis = sprintf('Eigenvector  %d',colEign);
        disp(Dis);
        for rowEign = 1:RowEign
            DisEign = sprintf('%d : %.4f',rowEign,Obj.EgnVec(rowEign,colEign));
            disp(DisEign);
        end
    end

end

