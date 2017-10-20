function Obj = Normalization( Obj )
%NORMALIZATION Summary of this function goes here
%   Detailed explanation goes here
    TempTranning = Obj.TranningFileData(1:end,1:end-1);
    TempTest = Obj.TestFileData(1:end,1:end-1);
    TranningMean = mean(TempTranning);
    TranningStd = std(TempTranning,1);
    
    TempTranning2 = (TempTranning - TranningMean);
    Obj.NormTranningFileData = TempTranning2 ./ TranningStd;
%    disp(Obj.NormTranningFileData);
    TEmpTEst2 = (TempTest - TranningMean);
    Obj.NormTestFileData = TEmpTEst2 ./ TranningStd;
%    disp(Obj.NormTestFileData);
end

