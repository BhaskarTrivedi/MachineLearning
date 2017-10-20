function Obj = SVDTest( Obj )
%PCATEST Summary of this function goes here
%   Detailed explanation goes here

    Obj.TsData = Obj.TestFileData(1:end,1:end-1); 
    
    [Row,Col] = size(Obj.TsData);
    [EignRow,EignCol] = size(Obj.EgnVec);
    
    for row = 1:Row
        TempX = Obj.TsData(row,:);
        TempXTrans = TempX.';
        Dis = sprintf('Test Object  %d',row-1);
        disp(Dis);
        for colEign = 1:EignCol
            tempEign = Obj.EgnVec(:,colEign);
            tempEignTans = tempEign.';
            ProjectionFunc = tempEignTans * TempXTrans;
            DisProj = sprintf('%d :  %.4f',colEign,ProjectionFunc);
            disp(DisProj);
        end
    end

end

