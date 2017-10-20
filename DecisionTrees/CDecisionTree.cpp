#include"CDecisionTree.h"
#include"CFileReading.h"
#include<vector>
#include<map>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<queue>

CDecisionTree::CDecisionTree()
{
        this->TranningTotalObject = 0;
        this->TestTotalObject = 0;
        this->Dimension = 0;
}

eErrorType CDecisionTree::ReadTranningFile(std::string FileName,eFileType FileType)
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
        char delit[] = " \t";
	std::vector<double> LineData;
        FileObj.OpenFile(FileName);
        while( SUCCESS == FileObj.GetLine(Line))
        {
		if(FileType == TRANNING)
			++this->TranningTotalObject;
		if(FileType == TEST)
			++this->TestTotalObject;
	}
	{
		char *der = (char *)Line.c_str();
                char* token = std::strtok(der,delit);
                LineData.clear();
                while(token!=NULL)
                {
                        double Value = atof(token);
                        LineData.push_back(Value);
                        token = std::strtok(NULL,delit);
                }
	}
	FileObj.CloseFile();
	int Col = LineData.size();
	if(FileType == TRANNING)
	{
        	this->Dimension = LineData.size() -1;
		this->TrainingData = AllocateMemory(this->TranningTotalObject,Col);
	}
	if(FileType == TEST)
		this->TestData = AllocateMemory(this->TestTotalObject,Col);


	//Initialize Tranning Matrix
	int RowIndex = 0;
	int ColIndex = 0;
        FileObj.OpenFile(FileName);
        while( SUCCESS == FileObj.GetLine(Line))
        {
		ColIndex = 0;
		char *der = (char *)Line.c_str();
                char* token = std::strtok(der,delit);
		double Value = -1;
                while(token!=NULL)
                {
                        Value = atof(token);
			if(FileType == TRANNING)
				this->TrainingData[RowIndex][ColIndex++] = Value;
			if(FileType == TEST)
				this->TestData[RowIndex][ColIndex++] = Value;
                        token = std::strtok(NULL,delit);
                }
		if(FileType == TRANNING)
			this->ClassNumber.insert(Value);
		RowIndex++;
	}
	FileObj.CloseFile();
/*	for(int rowindex = 0;rowindex < this->TranningTotalObject;rowindex++)
	{
		for(int colindex = 0;colindex <Col;colindex++)
		{
			std::cout<<this->TrainingData[rowindex][colindex]<<" ";
		}
		std::cout<<std::endl;
	}*/

/*	double attr =-1;
	double thr = -1;
	ChooseAttributeOptimized(this->TrainingData,this->TranningTotalObject,&attr,&thr);
	std::cout<<"Attribute : "<<attr<<",Threshold : "<<thr<<std::endl;
	double RandomAtr = -1;
	double Ranthr = -1;
	ChooseAttributeRandomized(this->TrainingData,this->TranningTotalObject,&RandomAtr,&Ranthr);
	std::cout<<"Random Attribute : "<<RandomAtr<<",Random Threshold : "<<Ranthr<<std::endl;i*/
	return Error;
}

double** CDecisionTree::AllocateMemory(int row1,int col1)
{
        double **Result = NULL;
        Result = (double**)malloc(sizeof(double*)*row1);
        for(int index = 0;index<row1;index++)
        {
                Result[index] = (double*)malloc(sizeof(double)*col1);
        }
        return Result;
}

void CDecisionTree::ChooseAttributeOptimized(double** Example,int Size,double* attribute,double* threshold,double* InfGain)
{
	double BestThreshold = -1;
	double BestAttribute = -1;
	double MaxGain = -1;
	for(int AttributeIndex = 0;AttributeIndex < this->Dimension;AttributeIndex++)
	{
		double Lowest = 999999999;
		double Highest = -1;
		for(int exampleIndex = 0; exampleIndex < Size; exampleIndex++)
		{
			if(Lowest > Example[exampleIndex][AttributeIndex])
				Lowest = Example[exampleIndex][AttributeIndex];
			if(Highest < Example[exampleIndex][AttributeIndex])
				Highest = Example[exampleIndex][AttributeIndex];
		}
		
		for(int Kindex = 1;Kindex<=50;Kindex++)
		{
			double TempThreshold = 	Lowest + Kindex * (Highest - Lowest) / 51;
			double TempGain = InformationGain(Example,Size,AttributeIndex,TempThreshold);	
			if(MaxGain < TempGain)
			{
				MaxGain = TempGain;
				BestAttribute = AttributeIndex;
				BestThreshold = TempThreshold;
//				std::cout<<"Max Gain :"<<MaxGain<<std::endl;
			}
//			std::cout<<"TempThreshold : "<<TempThreshold<<std::endl;
		}
	}	
	*attribute = BestAttribute;
	*threshold = BestThreshold;
	*InfGain = MaxGain;
}
		
double CDecisionTree::InformationGain(double** Example,int Size,int AttributeIndex,double Threshold)
{
	double Gain = 0;
	int TotalClass = ClassNumber.size();
	std::map<double,int> MapClass;
	double RootEntropy = 0;
	double LeftEntropy = 0;
	double RightEntropy = 0;
	std::map<double,int> LeftMapClass;
	std::map<double,int> RightMapClass;
	int LeftChildCount = 0;
	int RightChildCount =0;
	for(int RowIndex = 0;RowIndex<Size;RowIndex++)
	{
//		std::cout<<Example[RowIndex][this->Dimension]<<std::endl;
		std::map<double,int>::iterator MapItr = MapClass.find(Example[RowIndex][this->Dimension]);
		
		//Calculating Root class count
		if(MapItr == MapClass.end())
		{
			MapClass.insert(std::pair<double,int>(Example[RowIndex][this->Dimension],1));
		}
		else
		{
			MapItr->second = MapItr->second + 1;
		}

		//Calculating left child class count
		if(Example[RowIndex][AttributeIndex] < Threshold)
		{
			std::map<double,int>::iterator LeftMapItr = LeftMapClass.find(Example[RowIndex][this->Dimension]);
			LeftChildCount++;
			if(LeftMapItr == LeftMapClass.end())
				LeftMapClass.insert(std::pair<double,int>(Example[RowIndex][this->Dimension],1));
			else
				LeftMapItr->second = LeftMapItr->second + 1;
		}
		else
		{
			RightChildCount++;
			std::map<double,int>::iterator RightMapItr = RightMapClass.find(Example[RowIndex][this->Dimension]);
			if(RightMapItr == RightMapClass.end())
				RightMapClass.insert(std::pair<double,int>(Example[RowIndex][this->Dimension],1));
			else
				RightMapItr->second = RightMapItr->second + 1;
		}
	}	

	//Claculating RootEntropy
	for(std::map<double,int>::iterator ItrIndex = MapClass.begin();ItrIndex != MapClass.end();ItrIndex++)
	{
//		std::cout<<"Class : "<<ItrIndex->first<<" ,Count : "<<ItrIndex->second<<std::endl;
		double val = (double)ItrIndex->second/(double)Size;
		double logValue = log2(val);
		RootEntropy = RootEntropy + (-1 * val * logValue);
	}
//	std::cout<<"RootEntropy : "<<RootEntropy<<std::endl;

	//claculating Left Entropy
	for(std::map<double,int>::iterator LeftItrIndex = LeftMapClass.begin();LeftItrIndex != LeftMapClass.end();LeftItrIndex++)
	{
		double LeftVal = (double)LeftItrIndex->second/(double)LeftChildCount;
		double LeftLogValue = log2(LeftVal);
		LeftEntropy = LeftEntropy + ( -1 * LeftVal * LeftLogValue);
	}
	LeftEntropy = ((double)LeftChildCount/(double)Size) * LeftEntropy;


	//claculating Right Entropy
	for(std::map<double,int>::iterator RightItrIndex = RightMapClass.begin();RightItrIndex != RightMapClass.end();RightItrIndex++)
	{
		double RightVal = (double)RightItrIndex->second/(double)RightChildCount;
		double RightLogValue = log2(RightVal);
		RightEntropy = RightEntropy + ( -1 * RightVal * RightLogValue);
	}
	RightEntropy = ((double)RightChildCount/(double)Size) * RightEntropy;

	Gain = RootEntropy - LeftEntropy - RightEntropy;
	return Gain;
}
void CDecisionTree::ChooseAttributeRandomized(double** Example,int Size,double* attribute,double* threshold,double* InfGain)
{
	double BestThreshold = -1;
	double BestAttribute = -1;
	double MaxGain = -1;
	int AttributeIndex = rand() % this->Dimension;
	double Lowest = 999999999;
	double Highest = -1;
	for(int exampleIndex = 0; exampleIndex < Size; exampleIndex++)
	{
		if(Lowest > Example[exampleIndex][AttributeIndex])
			Lowest = Example[exampleIndex][AttributeIndex];
		if(Highest < Example[exampleIndex][AttributeIndex])
			Highest = Example[exampleIndex][AttributeIndex];
	}
		
	for(int Kindex = 1;Kindex<=50;Kindex++)
	{
		double TempThreshold = 	Lowest + Kindex * (Highest - Lowest) / 51;
		double TempGain = InformationGain(Example,Size,AttributeIndex,TempThreshold);	
		if(MaxGain < TempGain)
		{
			MaxGain = TempGain;
			BestAttribute = AttributeIndex;
			BestThreshold = TempThreshold;
//				std::cout<<"Max Gain :"<<MaxGain<<std::endl;
		}
//			std::cout<<"TempThreshold : "<<TempThreshold<<std::endl;
	}
	*attribute = BestAttribute;
	*threshold = BestThreshold;
	*InfGain = MaxGain;
}

void CDecisionTree::Distribution(double** Example,int Size,TreeNode *TreeN)
{
//	std::cout<<"Hello Distribution"<<std::endl;
	for(int RowIndex = 0;RowIndex<Size;RowIndex++)
	{
		std::map<double,double>::iterator MapItr = TreeN->mapDistribution->find(Example[RowIndex][this->Dimension]);
		if(MapItr != TreeN->mapDistribution->end())
		{
			MapItr->second = MapItr->second + 1;	
		}
	}

	for(std::map<double,double>::iterator MapItrDis=TreeN->mapDistribution->begin();
						MapItrDis!=TreeN->mapDistribution->end();MapItrDis++)
	{
		MapItrDis->second = MapItrDis->second / (double)Size;
	}
	
}
TreeNode* CDecisionTree::CreateNode()
{
	TreeNode* Temp = (TreeNode*)malloc(sizeof(TreeNode));
	Temp->NodeId = -1;
	Temp->FeatureId = -1;
	Temp->Threshold = -1;
	Temp->IGain = -1;
	Temp->mapDistribution = new std::map<double,double>();
	for(std::set<double>::iterator setItr = ClassNumber.begin();setItr != ClassNumber.end(); setItr++)
	{
		Temp->mapDistribution->insert(std::pair<double,double>(*setItr,0));
	}
	Temp->Left = NULL;
	Temp->Right = NULL;
}


void CDecisionTree::SetPrunningThreshold(double PrunningThr)
{
	this->PrunningThreshold = PrunningThr;
}
void CDecisionTree::SetTreeType(eTreeType TrTy)
{
	this->TreeType = TrTy;
	switch(this->TreeType)
	{
		case OPTIMIZED:
		case RANDOMIZED:
			this->TreeCount = 1;
			break;
		case FOREST3:
			this->TreeCount = 3;
			break;
		case FOREST15:
			this->TreeCount = 15;
			break;
		
	}
	this->Root = (TreeNode**)malloc(sizeof(TreeNode*)*this->TreeCount);
}


TreeNode* CDecisionTree::DecisionTreeLearning(double** Example,int Size,int nodeid)
{
	TreeNode *TNode = CreateNode();
//	std::cout<<this->PrunningThreshold<<std::endl;
	if(Size<this->PrunningThreshold)
	{
//		Distribution(Example,Size,TNode);	
		TNode->NodeId = nodeid;
		return TNode;
	}
	if(IsSameClass(Example,Size))
	{
		std::map<double,double>::iterator mapItr = TNode->mapDistribution->find( Example[0][this->Dimension] );
		if(mapItr != TNode->mapDistribution->end() )
		{
			mapItr->second = 1;
		}
		TNode->NodeId = nodeid;
		return TNode;
	}
	double BAttr = -1;
	double BThreshold = -1;
	double InfGain = -1;
	if(TreeType == OPTIMIZED)
		ChooseAttributeOptimized(Example,Size,&BAttr,&BThreshold,&InfGain);
	else
		ChooseAttributeRandomized(Example,Size,&BAttr,&BThreshold,&InfGain);
	TNode->FeatureId = BAttr;
	TNode->Threshold = BThreshold;
	TNode->IGain = InfGain;
/*	std::cout<<"Feature ID : "<<TNode->FeatureId<<std::endl;
	std::cout<<"Threashold ID : "<<TNode->Threshold<<std::endl;
	std::cout<<"Information Gain : "<<TNode->IGain<<std::endl;*/
	double **LeftExample;
	double **RightExample;
	int LeftSize;
	int RightSize;
	ExampleDivision(Example,Size,TNode->FeatureId,TNode->Threshold,&LeftExample,&RightExample,&LeftSize,&RightSize);
	TNode->Left = DecisionTreeLearning(LeftExample,LeftSize,2*nodeid);
	TNode->Right = DecisionTreeLearning(RightExample,RightSize,2*nodeid+1);
	TNode->NodeId = nodeid;
	Distribution(Example,Size,TNode->Left);	
	Distribution(Example,Size,TNode->Right);	
/*	for(int LftIndex = 0;LftIndex < LeftSize;LftIndex++)
	{
		for(int colLtIn = 0; colLtIn < this->Dimension + 1;colLtIn++)
		{
			std::cout<<LeftExample[LftIndex][colLtIn]<<" ";
		}
		std::cout<<std::endl;
	}
	for(int RgtIndex = 0;RgtIndex < RightSize;RgtIndex++)
	{
		for(int colLtIn = 0; colLtIn < this->Dimension + 1;colLtIn++)
		{
			std::cout<<RightExample[RgtIndex][colLtIn]<<" ";
		}
		std::cout<<std::endl;
	}*/
//	std::cout<<"Left Size : "<<LeftSize<<std::endl;
//	std::cout<<"Right Size : "<<RightSize<<std::endl;
	FreeMemory(LeftExample,LeftSize);
	FreeMemory(RightExample,RightSize);
	return TNode;
}
	
bool CDecisionTree::IsSameClass(double** Example,int Size)
{
	double ClassN = Example[0][this->Dimension];
	bool flag = true;
	for(int RowIndex = 0;RowIndex<Size;RowIndex++)
	{
		if(ClassN != Example[RowIndex][this->Dimension])
			flag = false;	
	}
//	std::cout<<flag<<std::endl;
	return flag;
}

void CDecisionTree::ExampleDivision(double **Example,int Size,double Attribute,double Threshold, double ***LeftExample,double ***RightExample,int *LeftSize,int* RightSize)
{
	int TempLftSz = 0;
	int TempRgtSz = 0;	
	int Atr = (int)Attribute;
	double **TempLftExm;
	double **TempRgtExm;
	for(int RowIndex = 0; RowIndex < Size;RowIndex++)
	{
		if(Example[RowIndex][Atr] < Threshold)
			TempLftSz++;
		else
			TempRgtSz++;
	}
//	std::cout<<"Left Size : "<<TempLftSz<<std::endl;
//	std::cout<<"Right Size : "<<TempRgtSz<<std::endl;
	TempLftExm = AllocateMemory(TempLftSz,this->Dimension+1);
	TempRgtExm = AllocateMemory(TempRgtSz,this->Dimension+1);
	int TempLfIndex = 0;
	int TempRtIndex = 0;

	for(int RowIndexNew = 0; RowIndexNew < Size;RowIndexNew++)
	{
		if(Example[RowIndexNew][Atr] < Threshold)
		{
			for(int ColLtIndex = 0;ColLtIndex < this->Dimension+1;ColLtIndex++)
			{
				TempLftExm[TempLfIndex][ColLtIndex] = Example[RowIndexNew][ColLtIndex];
			}
			TempLfIndex++;
		}
		else
		{
			for(int ColRtIndex = 0;ColRtIndex < this->Dimension+1;ColRtIndex++)
			{
				TempRgtExm[TempRtIndex][ColRtIndex] = Example[RowIndexNew][ColRtIndex];
			}
			TempRtIndex++;
		}
	}
	*LeftSize = TempLftSz;
	*RightSize = TempRgtSz;
	*LeftExample = TempLftExm;
	*RightExample = TempRgtExm;
}

void CDecisionTree::DecisionTreeTranning()
{
	for(int TreeIndex = 0; TreeIndex < this->TreeCount;TreeIndex++)
	{
		Root[TreeIndex] = DecisionTreeLearning(TrainingData,this->TranningTotalObject,1);
	}
/*	for(int TreeIndex = 0; TreeIndex < this->TreeCount;TreeIndex++)
	{
		std::cout<<Root[TreeIndex]->NodeId<<std::endl;
	}*/
}
		

void CDecisionTree::FreeMemory(double** Example,int Size)
{
	for(int RowIndex = 0; RowIndex<Size;RowIndex++)
	{
		delete[] Example[RowIndex];
	}
	
	delete[] Example;
}

void CDecisionTree::Display()
{
	for(int TreeIndex = 0; TreeIndex < this->TreeCount;TreeIndex++)
	{
		std::queue<TreeNode*> QueueObj;
		QueueObj.push(Root[TreeIndex]);
		while(!QueueObj.empty())
		{
			TreeNode *TN = QueueObj.front();
			QueueObj.pop();
			if(TN->Left!=NULL)
				QueueObj.push(TN->Left);
			if(TN->Right != NULL)
				QueueObj.push(TN->Right);
			printf("tree=%2d, node=%3d, feature=%2d, thr=%6.2lf, gain=%lf\n", TreeIndex, TN->NodeId, TN->FeatureId, TN->Threshold, TN->IGain);
		}
	}
}

void CDecisionTree::Classification()
{
/*	for(int rowindex = 0;rowindex < this->TestTotalObject;rowindex++)
	{
		for(int colindex = 0;colindex <this->Dimension + 1;colindex++)
		{
			std::cout<<this->TestData[rowindex][colindex]<<" ";
		}
		std::cout<<std::endl;
	}*/
	TreeNode *TreeNClas = NULL;
	double TotalAccuracy = 0;
	for(int rowindex = 0;rowindex < this->TestTotalObject;rowindex++)
	{
		std::map<double,double> AvgDistribution;
		for(int TreeIndex = 0; TreeIndex < this->TreeCount;TreeIndex++)
		{
	//		Root[TreeIndex] = DecisionTreeLearning(TrainingData,this->TranningTotalObject,1);
			TreeNClas = Root[TreeIndex];
			double thshld = 0;
			int Attr = 0;
			while(TreeNClas->Left != NULL && TreeNClas->Right != NULL)
			{
				thshld = TreeNClas->Threshold;
				Attr = (int)TreeNClas->FeatureId;

				if(this->TestData[rowindex][Attr] < thshld)
					TreeNClas = TreeNClas->Left;
				if(this->TestData[rowindex][Attr] >= thshld)
					TreeNClas = TreeNClas->Right;
			} 
			for(std::map<double,double>::iterator mapItrDis = TreeNClas->mapDistribution->begin();
				mapItrDis != TreeNClas->mapDistribution->end();mapItrDis++)
			{
				std::map<double,double>::iterator mapItr = AvgDistribution.find(mapItrDis->first);
				if(mapItr != AvgDistribution.end())
				{
					mapItr->second = mapItr->second + mapItrDis->second;
				}
				else
				{
					AvgDistribution.insert(std::pair<double,double>(mapItrDis->first,mapItrDis->second));
				}
			}
		}
		double PredictedClass = -1;
		double PredictedProbability = -1;
		double SameClass = 1;
		double Accuracy = 0;
		for(std::map<double,double>::iterator itrAvg = AvgDistribution.begin();itrAvg != AvgDistribution.end();
				itrAvg++)
		{
//			std::cout<<" Class :"<<itrAvg->first<<" "<<"Avg pr:"<<itrAvg->second;
			if(PredictedProbability < itrAvg->second)
			{
				PredictedProbability = itrAvg->second;
				PredictedClass = itrAvg->first;
				SameClass = 1;
			}
			else if(PredictedProbability == itrAvg->second)
			{
				if(this->TestData[rowindex][this->Dimension] != PredictedClass)
					PredictedClass = itrAvg->first;
				SameClass = SameClass + 1;
//				std::cout<<"Same pr detected";	
			}
		}
//		std::cout<<" Actual CLass "<<this->TestData[rowindex][this->Dimension]<<" Pred CLass :"<<PredictedClass;
//		std::cout<<std::endl;
		if(PredictedClass == this->TestData[rowindex][this->Dimension])
		{
			Accuracy = 1 / SameClass;
		}
		TotalAccuracy = TotalAccuracy + Accuracy;
		printf("ID=%5d,predicted=%3d,true=%3d,accuracy=%4.2lf\n",rowindex,(int)PredictedClass,
				(int)this->TestData[rowindex][this->Dimension],Accuracy);
//		printf("ID=%5d, predicted=%3d, true=%3d, accuracy=%4.2lf\n", rowindex, PredictedClass, this->TestData[rowindex][this->Dimension], Accuracy);
		AvgDistribution.clear();
	}
	double ClassificationAccuracy = TotalAccuracy / this->TestTotalObject;
	printf("classification accuracy=%6.4lf\n", ClassificationAccuracy);
}
