#include"CMixture.h"
#include"CFileReading.h"
#include<stdlib.h>
#include<limits.h>
#include<float.h>
#include<math.h>
#include<iostream>
#include<iomanip>

	
CMixture::CMixture(int NoMixture)
{
	this->NoofMixture = NoMixture;
}

void CMixture::SetFileName(std::string tranningFileName,std::string testFileName)
{
	this->TranningFileName = tranningFileName;
	this->TestFileName = testFileName;
}

eErrorType CMixture::CreateMixture()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
	char delit[] = " \t";
	FileObj.OpenFile(TranningFileName);
	this->Dimension = 0;
	while( SUCCESS == FileObj.GetLine(Line))
	{
		char *der = (char *)Line.c_str();
		char* token = std::strtok(der,delit);
		LineData.clear();
		this->TotalNoofObject++;
		while(token!=NULL)
		{
			double Value = atof(token);
			LineData.push_back(Value);
			token = std::strtok(NULL,delit);
		}
		double ClassValue = LineData.back();
		if( this->Dimension < (LineData.size()-1) )
                {
                	this->Dimension = LineData.size()-1;
                }
		std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.find(ClassValue);
		if(mapItr == mapMixtureClassification.end())
		{
			SMixtureDistribution MixDisObj;
			MixDisObj.NoofEntries = 1;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
				SMixtureDimension MixDimensionObj;
				MixDimensionObj.SmallestNumber = *Vecitr;
				MixDimensionObj.LargestNumber = *Vecitr;
				for(int index = 0; index< this->NoofMixture;++index)
				{
					MixDimensionObj.Mean.push_back(0);
					MixDimensionObj.StandardDeviation.push_back(1);
					MixDimensionObj.Weight.push_back(0);
					MixDimensionObj.MixtureProbability.push_back(0);
					MixDimensionObj.MixtureProbabilityMeanValue.push_back(0);
					MixDimensionObj.MixtureProbabilityVarianceValue.push_back(0);
				}
				MixDisObj.Dimension.push_back(MixDimensionObj);
			}
			mapMixtureClassification.insert(std::pair<double,SMixtureDistribution>(ClassValue,MixDisObj));
			
		}
		else
		{
			mapItr->second.NoofEntries++;
			std::vector<SMixtureDimension>::iterator itrMixDimension = mapItr->second.Dimension.begin();
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
				if(itrMixDimension != mapItr->second.Dimension.end())
				{
					if(*Vecitr < itrMixDimension->SmallestNumber)
					{
						itrMixDimension->SmallestNumber = *Vecitr;
					}
					if(*Vecitr > itrMixDimension->LargestNumber)
					{
						itrMixDimension->LargestNumber = *Vecitr;
					}
					itrMixDimension++;
				}
				else
				{
					SMixtureDimension MixDimensionObj;
					MixDimensionObj.SmallestNumber = *Vecitr;
					MixDimensionObj.LargestNumber = *Vecitr;
					for(int index = 0; index< this->NoofMixture;++index)
					{
						MixDimensionObj.Mean.push_back(0);
						MixDimensionObj.StandardDeviation.push_back(0);
						MixDimensionObj.Weight.push_back(0);
					}
					mapItr->second.Dimension.push_back(MixDimensionObj);
				}
			}
		}
	}
	
	for(int index=0;index<this->Dimension;index++)
	{
		Smallest.push_back(DBL_MAX);
		Largest.push_back(DBL_MIN);
	}

	
	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		for(int DimensionIndex = 0;DimensionIndex<this->Dimension;++DimensionIndex)
		{
//			std::cout<<"CLass : "<<mapItr->first<<",DImension : "<<DimensionIndex<<",Lowest : "
//				<<mapItr->second.Dimension[DimensionIndex].SmallestNumber<<",Highest : "<<
//					mapItr->second.Dimension[DimensionIndex].LargestNumber<<std::endl;
			if(Smallest[DimensionIndex] > mapItr->second.Dimension[DimensionIndex].SmallestNumber)
			{
				Smallest[DimensionIndex] =  mapItr->second.Dimension[DimensionIndex].SmallestNumber;
			}
			if(Largest[DimensionIndex] < mapItr->second.Dimension[DimensionIndex].LargestNumber)
			{
				Largest[DimensionIndex] = mapItr->second.Dimension[DimensionIndex].LargestNumber;	
			}
		}
	}
	

/*	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		
		for(int DimensionIndex = 0;DimensionIndex<this->Dimension;++DimensionIndex)
		{
			mapItr->second.Dimension[DimensionIndex].SmallestNumber = Smallest[DimensionIndex];
			mapItr->second.Dimension[DimensionIndex].LargestNumber = Largest[DimensionIndex];
		}
	}*/


	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		int DimIndex = 0;
		for(std::vector<SMixtureDimension>::iterator itrDimension = mapItr->second.Dimension.begin();
				itrDimension != mapItr->second.Dimension.end();++itrDimension)
		{
			double Lowest  = itrDimension->SmallestNumber;
			double Highest = itrDimension->LargestNumber;
			double Range = (Highest - Lowest)/this->NoofMixture;
			int Index = 0;
		//	std::cout<<
//			std::cout<<"Class :"<<mapItr->first<<",Attribute :"<<DimIndex<<",Range :"<<Range<<std::endl;
			for(std::vector<double>::iterator itrMean = itrDimension->Mean.begin();
					itrMean != itrDimension->Mean.end();++itrMean)
			{
				*itrMean = Lowest + Index*Range + Range/2;
				Index++;
			}
			for(std::vector<double>::iterator itrWeight = itrDimension->Weight.begin();
					itrWeight != itrDimension->Weight.end();++itrWeight)
			{
				*itrWeight = 1 / (double)this->NoofMixture;
			}
			DimIndex++;
		}
//		break;
	}
	CalculateClassProbability();
	FileObj.CloseFile();
	return Error;
}

eErrorType CMixture::EMAlgorithm()
{
	eErrorType Error = SUCCESS;
	for(int count =0;count<50;++count)
	{
		for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
		{	
			int DimensionIndex = 0;
			for(std::vector<SMixtureDimension>::iterator itrDimension = mapItr->second.Dimension.begin();
				itrDimension != mapItr->second.Dimension.end();++itrDimension)
			{
				for(int index = 0;index<this->NoofMixture;++index)
				{
					mapItr->second.Dimension[DimensionIndex].MixtureProbability[index] = 0;
					mapItr->second.Dimension[DimensionIndex].MixtureProbabilityMeanValue[index] = 0;
					mapItr->second.Dimension[DimensionIndex].MixtureProbabilityVarianceValue[index] = 0;
				}
				mapItr->second.Dimension[DimensionIndex].MixtureIndivisualProbability.clear();
				mapItr->second.Dimension[DimensionIndex].ProbabilityIndex = 0;
				++DimensionIndex;
			}
		}
		MeanCalculation();
		VarianceCalculation();
		WeightCalculation();
	}
	return Error;
}


eErrorType CMixture::MeanCalculation()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
	char delit[] = " \t";
	FileObj.OpenFile(TranningFileName);
	while( SUCCESS == FileObj.GetLine(Line))
	{
//		std::cout<<Line<<std::endl;
		char *der = (char *)Line.c_str();
		char* token = std::strtok(der,delit);
		LineData.clear();
		while(token!=NULL)
		{
			double Value = atof(token);
			LineData.push_back(Value);
			token = std::strtok(NULL,delit);
		}
		double ClassValue = LineData.back();
		int DimensionIndex = 0;
		for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
		{
			std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.find(ClassValue);
				std::vector<double> MixtureProbability;
			if(mapItr != mapMixtureClassification.end())
			{
		//		std::cout<<"Data : "<<*Vecitr<<std::endl;
				double TotalMixProbability = 0;
				for(int index = 0;index<this->NoofMixture;++index)
				{
					double mean = mapItr->second.Dimension[DimensionIndex].Mean[index];
					double StdDev = mapItr->second.Dimension[DimensionIndex].StandardDeviation[index];
					double Wgt = mapItr->second.Dimension[DimensionIndex].Weight[index];
					double MixProbability = GaussianValue(*Vecitr,mean,StdDev);
		//			std::cout<<"Gaussian Weight :"<<mapItr->second.Dimension[DimensionIndex].Weight[index]<<std::endl;
					MixProbability = MixProbability * mapItr->second.Dimension[DimensionIndex].Weight[index];
		//			std::cout<<"Gaussian Number :"<<index<<"Gaussian Prob :"<<MixProbability<<std::endl;
					MixtureProbability.push_back(MixProbability);
					TotalMixProbability = TotalMixProbability + MixProbability;
				}
				int index = 0;
				for(std::vector<double>::iterator itrMixProb = MixtureProbability.begin();
					itrMixProb != MixtureProbability.end(); ++itrMixProb)
				{
					double	ProbabilityCalculation = *itrMixProb / TotalMixProbability;
		//			std::cout<<"TOtal Probability :"<<TotalMixProbability<<std::endl;
		//			std::cout<<"ProbabilityCalculation : "<<ProbabilityCalculation<<std::endl;
					
					mapItr->second.Dimension[DimensionIndex].MixtureIndivisualProbability.push_back(ProbabilityCalculation);  
					
					mapItr->second.Dimension[DimensionIndex].MixtureProbability[index] = 
						mapItr->second.Dimension[DimensionIndex].MixtureProbability[index]+ProbabilityCalculation;
					
					mapItr->second.Dimension[DimensionIndex].MixtureProbabilityMeanValue[index] = 
						mapItr->second.Dimension[DimensionIndex].MixtureProbabilityMeanValue[index] + 
						ProbabilityCalculation * *Vecitr;
					++index;	
				}
			}
			++DimensionIndex;
		}
		//break;
	}
	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		int DimensionIndex = 0;
		for(std::vector<SMixtureDimension>::iterator itrDimension = mapItr->second.Dimension.begin();
				itrDimension != mapItr->second.Dimension.end();++itrDimension)
		{
			int Index = 0;
			for(std::vector<double>::iterator itrMean = itrDimension->Mean.begin();
					itrMean != itrDimension->Mean.end();++itrMean)
			{
				*itrMean = mapItr->second.Dimension[DimensionIndex].MixtureProbabilityMeanValue[Index] /
					mapItr->second.Dimension[DimensionIndex].MixtureProbability[Index];
//				std::cout<<"Mean "<<mapItr->second.Dimension[DimensionIndex].MixtureProbabilityMeanValue[Index]<<std::endl;
//				std::cout<<"Totoa "<<mapItr->second.Dimension[DimensionIndex].MixtureProbability[Index]<<std::endl;
				++Index;
			}
			++DimensionIndex;
		}
	}
	FileObj.CloseFile();
	return Error;
}


eErrorType CMixture::VarianceCalculation()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
	char delit[] = " \t";
	FileObj.OpenFile(TranningFileName);
	while( SUCCESS == FileObj.GetLine(Line))
	{
//		std::cout<<std::endl<<Line<<std::endl;
		char *der = (char *)Line.c_str();
		char* token = std::strtok(der,delit);
		LineData.clear();
		while(token!=NULL)
		{
			double Value = atof(token);
			LineData.push_back(Value);
			token = std::strtok(NULL,delit);
		}
		double ClassValue = LineData.back();
		int DimensionIndex = 0;
	//	std::cout<<"variance CheckPoint 1"<<std::endl;
		std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.find(ClassValue);
			std::vector<double> MixtureProbability;
		if(mapItr != mapMixtureClassification.end())
		{
	//	std::cout<<"Size of "<<mapItr->second.Dimension[DimensionIndex].MixtureIndivisualProbability.size()<<std::endl;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
//				std::cout<<" "<<*Vecitr;
				for(int index = 0;index<this->NoofMixture;++index)
				{
					int CurrentIndex = mapItr->second.Dimension[DimensionIndex].ProbabilityIndex;
	//				std::cout<<"CLass :"<<mapItr->first<<"Dimension :"<<DimensionIndex<<"Current Index "<<CurrentIndex<<std::endl;
			//		double VariableProb  = 0;
					double VariableProb = mapItr->second.Dimension[DimensionIndex].MixtureIndivisualProbability[CurrentIndex];

/*					if(1 == mapItr->first && 4 == DimensionIndex)
					{
						std::cout<<"Class : "<<mapItr->first<<" Dimension :"<<DimensionIndex<<" Gaussian :"<<index<<
								" Variable value : "<<VariableProb<<std::endl;
				}*/
					double CurrentMean = mapItr->second.Dimension[DimensionIndex].Mean[index]; 
					VariableProb = VariableProb * (*Vecitr - CurrentMean) * (*Vecitr - CurrentMean);
					
/*					if(1 == mapItr->first && 4 == DimensionIndex)
					{
//						std::cout<<"Variable Prob :"<<VariableProb<<"Value :"<<*Vecitr<<"Current mean: "
//							<<CurrentMean<<std::endl;
					}*/
					mapItr->second.Dimension[DimensionIndex].MixtureProbabilityVarianceValue[index] = 
						mapItr->second.Dimension[DimensionIndex].MixtureProbabilityVarianceValue[index] 
									+ VariableProb;
					++mapItr->second.Dimension[DimensionIndex].ProbabilityIndex;
				}
				++DimensionIndex;
			}
		}
	//	std::cout<<"variance CheckPoint 3"<<std::endl;
	}
	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		int DimensionIndex = 0;
		for(std::vector<SMixtureDimension>::iterator itrDimension = mapItr->second.Dimension.begin();
				itrDimension != mapItr->second.Dimension.end();++itrDimension)
		{
			int Index = 0;
			for(std::vector<double>::iterator itrVariance = itrDimension->StandardDeviation.begin();
					itrVariance != itrDimension->StandardDeviation.end();++itrVariance)
			{
				double variance = mapItr->second.Dimension[DimensionIndex].MixtureProbabilityVarianceValue[Index] /
							mapItr->second.Dimension[DimensionIndex].MixtureProbability[Index];	
/*				if(0 == mapItr->second.Dimension[DimensionIndex].MixtureProbabilityVarianceValue[Index])
				{
					std::cout<<"Class : "<<mapItr->first<<" Dimension :"<<DimensionIndex<<" Variance Zero Deytected"<<std::endl;
				}*/
				if(0.0001 > variance)
				{
					variance = 0.0001;
				}
				variance = sqrt(variance);
				*itrVariance = variance;
				++Index;
			}
			++DimensionIndex;
		}
	}
	FileObj.CloseFile();
	return Error;
}

eErrorType CMixture::WeightCalculation()
{
	eErrorType Error = SUCCESS;
	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		int DimensionIndex = 0;
		for(std::vector<SMixtureDimension>::iterator itrDimension = mapItr->second.Dimension.begin();
				itrDimension != mapItr->second.Dimension.end();++itrDimension)
		{
			double TotalProbability = mapItr->second.Dimension[DimensionIndex].MixtureProbability[0]
					+ mapItr->second.Dimension[DimensionIndex].MixtureProbability[1] 
					+ mapItr->second.Dimension[DimensionIndex].MixtureProbability[2];
			for(int index = 0;index<this->NoofMixture;++index)
			{
				mapItr->second.Dimension[DimensionIndex].Weight[index] = 
					mapItr->second.Dimension[DimensionIndex].MixtureProbability[index] / 
						TotalProbability;
			}
			++DimensionIndex;
		}
	}
	return Error;
}

double CMixture::GaussianValue(double value,double mean,double stDev)
{
	double denominator;
	double pi = 3.1415926535897932384626;
	denominator = 2 * pi;
	denominator = sqrt(denominator);
	double Numerator = value - mean;
	double GaussianData = 0; 
//	std::cout<<" Data :"<<value<<",Mean:"<<mean<<"St Dev:"<<stDev<<std::endl;
	if( 0.01 > stDev)
	{
		stDev = 0.01;
	//	std::cout<<"Hello min stddev"<<std::endl;
	}
	if(0 != stDev)
	{
		Numerator = Numerator * Numerator;
		Numerator = Numerator / ( 2 * stDev * stDev);
		Numerator = exp( -1 * Numerator);
		denominator = denominator * stDev;
		GaussianData = Numerator / denominator;
	}
	else
	{
		std::cout<<"Hello Exception  mixture:"<<std::endl;
		if(value == mean)
		{
			GaussianData = 0.99;
		}
		else
		{
			GaussianData = 0.01;
		}
	}
	if(GaussianData == 0)
	{
//		GaussianData = 0.001;
	}
/*	if( 0 == GaussianData)
	{
		double kNumerator = value - mean;
		std::cout<<"Knumerator :"<<kNumerator<<std::endl;
		kNumerator = kNumerator * kNumerator;
		std::cout<<"Knumerator :"<<kNumerator<<std::endl;
		kNumerator = kNumerator / ( 2 * stDev * stDev);
		std::cout<<"Knumerator :"<<kNumerator<<std::endl;
		kNumerator = exp( -1 * kNumerator);
		std::cout<<"Knumerator :"<<kNumerator<<std::endl;
		std::cout<<"High :"<<"Value :"<<value<<",mean :"<<mean<<",stdd :"<<stDev<<std::endl;
	}*/
//	std::cout<<",Gaussian Prob :"<<GaussianData<<std::endl;
	return GaussianData;
	
}
	
eErrorType CMixture::CalculateClassProbability()
{
	eErrorType Error = SUCCESS;
	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		if( 0 < TotalNoofObject )
		{
			mapItr->second.Probability = (double)mapItr->second.NoofEntries / (double)TotalNoofObject; 
		}
	}
	return Error;
}


void CMixture::Display()
{
	for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
	{
		int DimensionIndex = 0;
		for(std::vector<SMixtureDimension>::iterator itrDimension = mapItr->second.Dimension.begin();
				itrDimension != mapItr->second.Dimension.end();++itrDimension)
		{
			for(int index = 0;index<this->NoofMixture;++index)
			{
				std::cout<<"Class "<<(int)mapItr->first<<", attribute "<<DimensionIndex<<", Gaussian "<<index;
				std::cout<<std::fixed<<std::setprecision(2)<<",mean "<<mapItr->second.Dimension[DimensionIndex].Mean[index];
				std::cout<<", std "<<mapItr->second.Dimension[DimensionIndex].StandardDeviation[index]<<std::endl;
			}
			++DimensionIndex;
		}
	}
}
	

eErrorType CMixture::Classification()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
	char delit[] = " \t";
	FileObj.OpenFile(TestFileName);
	double AverageAccuracy = 0;
	int ObjectID =0;
	while( SUCCESS == FileObj.GetLine(Line))
	{
	//	std::cout<<Line<<std::endl;
		char *der = (char *)Line.c_str();
		char* token = std::strtok(der,delit);
		LineData.clear();
		while(token!=NULL)
		{
			double Value = atof(token);
			LineData.push_back(Value);
			token = std::strtok(NULL,delit);
		}
		double ClassValue = LineData.back();
		double CurrentNumerator = 0;
		double HistogramProbability = 0;
		double PredictedClassCount = 0;
		int PredictedClass = (int)ClassValue;
		std::map<double,double> ConditionalProbability;
		double Denominator = 0;
		ConditionalProbability.clear();
		for(std::map<double,SMixtureDistribution>::iterator mapItr = mapMixtureClassification.begin();
			mapItr != mapMixtureClassification.end();++mapItr)
		{
			int DimensionIndex = 0;
			CurrentNumerator = mapItr->second.Probability;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
				double TotalMixProbability = 0;
				for(int index = 0;index<this->NoofMixture;++index)
				{
					double mean = mapItr->second.Dimension[DimensionIndex].Mean[index];
					double StdDev = mapItr->second.Dimension[DimensionIndex].StandardDeviation[index];
					double Wgt = mapItr->second.Dimension[DimensionIndex].Weight[index];
					double MixProbability = GaussianValue(*Vecitr,mean,StdDev);
//					std::cout<<"Class :"<<mapItr->first<<",Data :"<<*Vecitr<<",Mean :"<<mean<<",StdDev :"<<StdDev
//						<<",Probability :"<<MixProbability<<std::endl;
				//	std::cout<<"Mix prob :"<<MixProbability<<std::endl;
//					std::cout<<MixProbability<<" * "<<mapItr->second.Dimension[DimensionIndex].Weight[index];
					MixProbability = MixProbability * mapItr->second.Dimension[DimensionIndex].Weight[index];
//					std::cout<<" : "<<MixProbability<<std::endl;
//					std::cout<<TotalMixProbability<<" + "<<MixProbability;
					TotalMixProbability = TotalMixProbability + MixProbability;
//					std::cout<<" "<<TotalMixProbability<<std::endl;
				}
//				std::cout<<"CUrrent NUmerator :"<<CurrentNumerator<<" * "<<TotalMixProbability;
				CurrentNumerator = CurrentNumerator * TotalMixProbability;
//				std::cout<<": "<<CurrentNumerator<<std::endl;
				++DimensionIndex;
			}
//			std::cout<<"Denominator :"<<Denominator<<" + "<<CurrentNumerator;
			Denominator = Denominator + CurrentNumerator;
//			std::cout<<" :"<<Denominator<<std::endl;
			ConditionalProbability.insert(std::pair<double,double>(mapItr->first,CurrentNumerator));
		}
		for(std::map<double,double>::iterator itrCdProb = ConditionalProbability.begin();itrCdProb!=ConditionalProbability.end();
				++itrCdProb)
		{	
			
			double CurrentHisProb = 0;
			if(0!=Denominator)
			{
				CurrentHisProb = itrCdProb->second/Denominator;
			}
			else
			{
				CurrentHisProb = 1/10;
			}
			
	//		std::cout<<"Numerator :"<<itrCdProb->second;
	//		std::cout<<",Current HisProb :"<<CurrentHisProb;
	//		std::cout<<",Denominator  :"<<Denominator<<std::endl;
			if(0 == Denominator)
			{
//				std::cout<<"Denominator :"<<Denominator<<std::endl;
			}
			if(CurrentHisProb > HistogramProbability)
			{
				HistogramProbability = CurrentHisProb;	
				PredictedClass = (int)itrCdProb->first;
				PredictedClassCount = 1;
//				std::cout<<"Predicted CLass count"<<PredictedClassCount<<std::endl;
			}
			else if(CurrentHisProb == HistogramProbability)
			{
				if(ClassValue == itrCdProb->first)
				{
					PredictedClass = ClassValue;
				}
				PredictedClassCount++;
		//		std::cout<<"Predicted CLass Equal:"<<PredictedClassCount<<std::endl;
			}
			else
			{
				
				
//				std::cout<<"else ,Current HisProb :"<<CurrentHisProb<<std::endl;
			}
		}
		double accuracy = 0;	
		if(ClassValue == PredictedClass)
		{
			accuracy = 1/double(PredictedClassCount);
			AverageAccuracy = AverageAccuracy + accuracy;
		//	std::cout<<"AverageAccuracy : "<<AverageAccuracy<<std::endl;
		}
//		std::cout<<"Prob : "<<HistogramProbability<<std::endl;
		printf("ID=%5d, predicted=%3d, probability = %.4lf, true=%3d, accuracy=%4.2lf\n", 
					ObjectID,PredictedClass, HistogramProbability, (int)ClassValue, accuracy);
		ObjectID++;
	/*	if(2==ObjectID)
		{
			break;
		}*/
	}
	AverageAccuracy = AverageAccuracy / ObjectID;
	printf("classification accuracy=%6.4lf\n", AverageAccuracy);
	FileObj.CloseFile();
	return Error;
}
