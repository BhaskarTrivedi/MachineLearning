function Obj = SVDEignvalueCalculate( Obj, TraData )
%PCATRANNING Summary of this function goes here
%   Detailed explanation goes here
%    Obj.TrData = TraData; 
 %   disp(Obj.TrData);
    Obj.EgnVec(:,:) = [];
    Obj.EgnValues(:,:) = [];
    [Row,Col] = size(TraData); 
    for OutDm = 1:Obj.OutputDimension
        TempEgnVec = ones([Col,1]);
   %     CoveranceMat = cov(TraData);
        for Itr = 1:Obj.Iteration      
            EgnVecMul = TraData * TempEgnVec;
            TempEgnVec = EgnVecMul / norm(EgnVecMul);
            Obj.EgnValues(OutDm,1) = norm(EgnVecMul);
        end
        if OutDm == 1
            Obj.EgnVec = TempEgnVec;
        else
            Obj.EgnVec(:,end+1) = TempEgnVec;
        end
        for row = 1:Row
            TemXValue = TraData(row,:);
            TemXValueTrans = TemXValue.';
            Temp = TemXValueTrans - TempEgnVec.' * TemXValueTrans * TempEgnVec;
            TraData(row,:) = Temp;
        end
    end
%{
    [RowEign,ColEign] = size(Obj.EgnVec);    
    for colEign = 1:ColEign
        Dis = sprintf('Eigenvector  %d',colEign);
        disp(Dis);
        for rowEign = 1:RowEign
            DisEign = sprintf('%d : %.4f',rowEign,Obj.EgnVec(rowEign,colEign));
            disp(DisEign);
        end
    end
%}   
    %{
    [RowEignval,ColEignval] = size(Obj.EgnValues);  
    disp('EignValues');
    for colEignv = 1:ColEignval
        for rowEignv = 1:RowEignval
            disp(Obj.EgnValues(rowEignv,colEignv));
        end
    end
    %}
end

