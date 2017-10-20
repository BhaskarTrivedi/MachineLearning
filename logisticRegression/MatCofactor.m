function CoffMat = MatCofactor( Mat )
%MATCOFACTOR Summary of this function goes here
%   Detailed explanation goes here

    [rows,cols] = size(Mat);
    tempCof = ones(rows,cols);
    temp = Mat;
    for row = 1:rows
        for col = 1:cols
            temp([row],:)=[];
            temp(:,[col])=[];
            tempCof = ((-1)^(row+col))*det(temp);
            temp = Mat;
        end
    end
    CoffMat = tempCof;
end

