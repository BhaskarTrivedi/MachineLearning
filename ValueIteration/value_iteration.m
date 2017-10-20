function Y = value_iteration( EnvironmentFile,NonTerminalReward,Gamma,Iteration )
%VALUE_ITERATION Summary of this function goes here
%   Detailed explanation goes here

FR = FileRead;
FR = ReadEnvironmentFile(FR,EnvironmentFile);


EnvironmentFileFileData = GetEnvironmentFile(FR);

CMarkovDecisionProcessObj = CMarkovDecisionProcess;

CMarkovDecisionProcessObj = CMarkovDecisionProcessObj.SetEnvironmentData(EnvironmentFileFileData);
CMarkovDecisionProcessObj = CMarkovDecisionProcessObj.SetIteration(Iteration);
CMarkovDecisionProcessObj = CMarkovDecisionProcessObj.SetNonTerminalReward(NonTerminalReward);
CMarkovDecisionProcessObj = CMarkovDecisionProcessObj.SetGamma(Gamma);
CMarkovDecisionProcessObj = CMarkovDecisionProcessObj.MDPLearning();

end

