classdef FileRead < matlab.mixin.CustomDisplay
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Hidden = true,Access = private)
        TranningFileData
        TestFileData
    end
  
    methods
        function Obj = ReadTranningFile(Obj,TranningFileName)
            Obj.TranningFileData = importdata(TranningFileName);
        end
        function Obj = ReadTestFile(Obj,TestFileName)
            Obj.TestFileData = importdata(TestFileName);
        end
        function TRFileData = GetTranningData(obj)
            TRFileData = obj.TranningFileData;
        end
        function TeFileData = GetTestData(obj)
            TeFileData = obj.TestFileData;
        end

    end
    
end

