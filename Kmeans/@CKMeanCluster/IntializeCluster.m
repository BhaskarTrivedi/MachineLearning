function Obj = IntializeCluster( Obj )
%ASSIGNINTIALIZECLUSTER Summary of this function goes here
%   Detailed explanation goes here

    Obj.TestDataWOClass = Obj.TestFileData(1:end,1:end-1); 
    Obj.TestDataWOClass(:,end+1) = 0;
    [Row,Col] = size(Obj.TestDataWOClass);
    RandomCluster = randi(Obj.NoOfCluster,Row,1);
    
    Obj.TestDataWOClass(:,end) = RandomCluster;
    
    Obj.ClusterMean = grpstats( Obj.TestDataWOClass(:,1:end-1),Obj.TestDataWOClass(:,end) );
    
    
    %disp(Obj.TestDataWOClass);
    %disp(RandomCluster);
    %disp(size(RandomCluster));

end

