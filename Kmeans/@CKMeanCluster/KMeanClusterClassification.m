function Obj = KMeanClusterClassification( Obj )
%KMEANCLUSTERCLASSIFICATION Summary of this function goes here
%   Detailed explanation goes here
    OldError = 0;
    Obj = Obj.IntializeCluster(); 
    Obj = Obj.ErrorClaculation();
    OldError = Obj.ErrorValue;
    DisError = sprintf('After initialization: error = %.4f',Obj.ErrorValue);
    disp(DisError);
    Currentcount = 0;
    for CurrentItr = 1:Obj.Iteration
 %   while(1)
        Currentcount = Currentcount + 1;
        OldError = Obj.ErrorValue;
        Obj = Obj.UpdateCluster();
        Obj = Obj.ErrorClaculation();               
        DisError = sprintf('After iteration %d: error = %.4f',Currentcount,Obj.ErrorValue);
        disp(DisError);
   %     if(Obj.ErrorValue == OldError)
   %         break;
   %     end
    end

end

