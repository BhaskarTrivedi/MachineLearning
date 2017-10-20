classdef FileRead < matlab.mixin.CustomDisplay
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Hidden = true,Access = private)
        TranningFileData = struct('object_ID',{},'class_label',{},'sign_meaning',{},'dominant_hand_trajectory',{})
        TestFileData = struct('object_ID',{},'class_label',{},'sign_meaning',{},'dominant_hand_trajectory',{})
    end
  
    methods
        Obj = ReadTranningFile(Obj,TranningFileName)
        Obj = ReadTestFile(Obj,TestFileName)

        function TRFileData = GetTranningData(obj)
            TRFileData = obj.TranningFileData;
        end
        function TeFileData = GetTestData(obj)
            TeFileData = obj.TestFileData;
        end

    end
    methods(Access = private)
         
    end
    
end

