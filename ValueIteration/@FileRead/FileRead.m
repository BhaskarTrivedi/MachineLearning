classdef FileRead < matlab.mixin.CustomDisplay
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Hidden = true,Access = private)
        EnvironmentFileData
    end
  
    methods
        Obj = ReadEnvironmentFile(Obj,TranningFileName)

        function ERFileData = GetEnvironmentFile(obj)
            ERFileData = obj.EnvironmentFileData;
        end

    end
    
end

