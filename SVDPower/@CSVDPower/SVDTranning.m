function Obj = SVDTranning( Obj )
%SVDTRANNING Summary of this function goes here
%   Detailed explanation goes here

% Calculate U matrix 
    TempU = Obj.TranningFileData*Obj.TranningFileData.';
    Obj = Obj.SVDEignvalueCalculate(TempU);    
    Obj.MatU = Obj.EgnVec;
    
    % Calculate S matrix 
    for RowS = 1:Obj.OutputDimension
        for ColS = 1:Obj.OutputDimension
            if(RowS ~= ColS)
                Obj.MatS(RowS,ColS) = 0;
            else
                Obj.MatS(RowS,ColS) = sqrt(Obj.EgnValues(RowS,1));
            end
        end
    end
    
    % Calculate V matrix 
    TempV = Obj.TranningFileData.' * Obj.TranningFileData;
    Obj = Obj.SVDEignvalueCalculate(TempV);   
    Obj.MatV = Obj.EgnVec;
    
    %Calculate A Matrix
    
    Obj.MatReconstruction = Obj.MatU * Obj.MatS * Obj.MatV.';

    
     %Print U Matix
    disp('Matrix U:');
    [RowEign,ColEign] = size(Obj.MatU);   
    for rowEign = 1:RowEign  
   %     DisEign = sprintf('Row %3d: %8.4f',rowEign,Obj.EgnVec(rowEign,:));
        DisEign = sprintf('%8.4f',Obj.MatU(rowEign,:));
        Disp = sprintf('Row %3d',rowEign);
        DispOutput = sprintf('%s:%s',Disp,DisEign);
        disp(DispOutput);
    end
    
    %Print S Matix
    disp('Matrix S:');
    [RowEignS,ColEignS] = size(Obj.MatS);   
    for rowEignS = 1:RowEignS  
   %     DisEign = sprintf('Row %3d: %8.4f',rowEign,Obj.EgnVec(rowEign,:));
        DisEignS = sprintf('%8.4f',Obj.MatS(rowEignS,:));
        DispS = sprintf('Row %3d',rowEignS);
        DispOutputS = sprintf('%s:%s',DispS,DisEignS);
        disp(DispOutputS);
    end
    
    %Print V Matix
    disp('Matrix V:');
    [RowEignV,ColEignV] = size(Obj.MatV);   
    for rowEignV = 1:RowEignV  
   %     DisEign = sprintf('Row %3d: %8.4f',rowEign,Obj.EgnVec(rowEign,:));
        DisEignV = sprintf('%8.4f',Obj.MatV(rowEignV,:));
        DispV = sprintf('Row %3d',rowEignV);
        DispOutputV = sprintf('%s:%s',DispV,DisEignV);
        disp(DispOutputV);
    end
    
    %Print Reconstruction Matix
     disp('Reconstruction (U*S*V''):');
    [RowEignRe,ColEignRe] = size(Obj.MatReconstruction);   
    for rowEignRe = 1:RowEignRe  
   %     DisEign = sprintf('Row %3d: %8.4f',rowEign,Obj.EgnVec(rowEign,:));
        DisEignRe = sprintf('%8.4f',Obj.MatReconstruction(rowEignRe,:));
        DispRe = sprintf('Row %3d',rowEignRe);
        DispOutputRe = sprintf('%s:%s',DispRe,DisEignRe);
        disp(DispOutputRe);
    end
end

