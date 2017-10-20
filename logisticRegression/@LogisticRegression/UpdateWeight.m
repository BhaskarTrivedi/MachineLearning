function Obj = UpdateWeight( Obj )
%UPDATEWEIGHT Summary of this function goes here
%   Detailed explanation goes here
  %  DeletedRow = 1;
    PhiT = Obj.PhiMatrix.';
    Obj.ErrorNew = PhiT * ( Obj.ActivationOutput - Obj.ClassOutput);
    HessianMatrix = PhiT * Obj.RMatrix * Obj.PhiMatrix;
%    disp(size(HessianMatrix));
%{
    CoffHessianMatrix = MatCofactor(HessianMatrix);
    DetHessianMatrix = det(HessianMatrix);
    if(DetHessianMatrix == 0)
        DetHessianMatrix = 1;
    disp(DetHessianMatrix);
%}
 %{
    while(1)
        DetHessianMatrix = det(HessianMatrix);
        disp('Detmat');
%        disp(DetHessianMatrix);
        disp(HessianMatrix);
        if( 0 == DetHessianMatrix)
            HessianMatrix = HessianMatrix + 0.0001;
%            break;
        else
%            disp('break')
             break;
        end
        
end
 %}
    
    
 %   HessianMatrixInverse = CoffHessianMatrix / DetHessianMatrix;
    HessianMatrixInverse = pinv(HessianMatrix);
 %   disp(HessianMatrixInverse);
    Obj.WeightNew = Obj.WeightOld - HessianMatrixInverse * Obj.ErrorNew;
  %  disp(Obj.WeightNew)

end

