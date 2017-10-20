function Obj = LogisticsClassification( Obj )
%LOGISTICSCLASSIFICATION Summary of this function goes here
%   Detailed explanation goes here
    [rows,cols] = size(Obj.TestFileData); 
    WeightTrans = Obj.WeightNew.';
    phix = zeros(Obj.Degree * Obj.Dimension + 1,1);
    TrueClass = 0;
    PredictedClass = 0;
    TotalCorrectClassification = 0;
    for row = 1:rows
        phirow = 1;
        for col = 1:cols
            Accuracy = 0;
            if( 1 == col)
                phix(phirow,1) = 1;
                phirow = phirow + 1;
            end
            if(col ~= cols)
                phix(phirow,1) = Obj.TestFileData(row,col);
                phirow = phirow + 1;
                if( 2 == Obj.Degree)
                    phix(phirow,1) = Obj.TestFileData(row,col) * Obj.TestFileData(row,col);
                    phirow = phirow + 1;
                end
            else
                if( 1 == Obj.TestFileData(row,col))
                    TrueClass = 1;
                else
                    TrueClass = 0;
                end
            end
        end
    %    disp((WeightTrans));
     %   disp((phix));
        SigmoidalCoefficient = WeightTrans * phix;
        if( 0 < SigmoidalCoefficient)
            PredictedClass = 1;
            if(PredictedClass == TrueClass)
                Accuracy = 1;
            end
        elseif( 0 > SigmoidalCoefficient)
            PredictedClass = 0;
            if(PredictedClass == TrueClass)
                Accuracy = 1;
            end
        else
            Accuracy = 0.5;
        end
        TotalCorrectClassification = TotalCorrectClassification + Accuracy;
        express = 1 + exp( -1 * SigmoidalCoefficient);
        ClassProbability = 1 / express;
        if( 0 == PredictedClass)
            ClassProbability = 1 - ClassProbability;
        end
        ObjectDis = sprintf('ID=%5d, predicted=%3d, probability = %.4f, true=%3d, accuracy=%4.2f',row-1,PredictedClass,ClassProbability,TrueClass,Accuracy);
        disp(ObjectDis);
    end
    Dis = sprintf('classification accuracy=%.4f',TotalCorrectClassification/rows);
    disp(Dis);
end

