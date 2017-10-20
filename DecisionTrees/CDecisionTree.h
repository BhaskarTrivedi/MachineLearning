#ifndef CDECISIONTREE_H
#define CDECISIONTREE_H

#include"Utility.h"
#include<string>
#include<set>

class CDecisionTree
{
	public:
		CDecisionTree();
		eErrorType ReadTranningFile(std::string tranningFileName,eFileType FileType);		
		void SetPrunningThreshold(double PrunningThr);
		void SetTreeType(eTreeType TrTy);
		void DecisionTreeTranning();
		void Classification();
		void Display();
	private:
		TreeNode* DecisionTreeLearning(double** Example,int Size,int nodeid);
		double InformationGain(double** Example,int Size,int AttributeIndex,double TempThreshold);
		TreeNode* CreateNode();
		double** AllocateMemory(int Rows,int Cols);
		void FreeMemory(double** Example,int Size);
		bool IsSameClass(double** Example,int Size);
		void ChooseAttributeOptimized(double** Example,int Size,double* attribute,double* thresold,double* InfGain);
		void ChooseAttributeRandomized(double** Example,int Size,double* attribute,double* thresold,double* InfGain);
		void Distribution(double** Example,int Size,TreeNode *TreeN);
		void ExampleDivision(double **Example,int Size,double Attribute,double Threshold ,double ***LeftExample,double ***RightExample,int *LeftSize,int* RightSize);

		double **TrainingData;
		double **TestData;
		int TranningDataSize;
		int TranningTotalObject;
		int TestTotalObject;
		int Dimension;
		int ClassSize;
		std::set<double> ClassNumber;
		int TreeCount;
		TreeNode **Root;
		double PrunningThreshold;
		eTreeType TreeType;
	
};

#endif
