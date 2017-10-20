#include"CDecisionTree.h"
#include<stdlib.h>
#include<cstring>
#include<iostream>

void DecisionTreeClassification(std::string TranningFileName,std::string TestFileName,std::string TreeOption,std::string Threshold);

int main(int argc,char*argv[])
{
	if(argc < 5)
        {
                std::cout<<"Too few parameter!! "<<std::endl;
                return 0;
        }

	DecisionTreeClassification(argv[1],argv[2],argv[3],argv[4]);

	return 0;
}

void DecisionTreeClassification(std::string TranningFileName,std::string TestFileName,std::string TreeOption,std::string PrThreshold)
{
	eTreeType TreeType;
	eFileType TranningFileType = TRANNING;
	eFileType TestFileType = TEST;

	double Prthr= 0;
        char delit[] = "<>";
        char *der = (char *)PrThreshold.c_str();
        char* token = std::strtok(der,delit);
        while(token!=NULL)
        {
                Prthr = atoi(token);
                token = std::strtok(NULL,delit);
        }

	if(!TreeOption.compare("optimized"))
	{
		TreeType = OPTIMIZED;
	}
	else if(!TreeOption.compare("randomized"))
	{
		TreeType = RANDOMIZED;
	}
	else if(!TreeOption.compare("forest3"))
	{
		TreeType = FOREST3;
	}
	else if(!TreeOption.compare("forest15"))
	{
		TreeType = FOREST15;
	}
	CDecisionTree DecisionTreeObj;	
	DecisionTreeObj.SetTreeType(TreeType);
	DecisionTreeObj.SetPrunningThreshold(Prthr);
	DecisionTreeObj.ReadTranningFile(TranningFileName,TranningFileType);
	DecisionTreeObj.DecisionTreeTranning();
	DecisionTreeObj.Display();
	DecisionTreeObj.ReadTranningFile(TestFileName,TestFileType);
	DecisionTreeObj.Classification();
}
