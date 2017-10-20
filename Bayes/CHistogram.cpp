#include"CHistogram.h"
#include"CFileReading.h"
#include<stdlib.h>
#include<limits.h>
#include<float.h>
#include<iomanip>
#include<iostream>

CHistogram::CHistogram(int noofBin)
{
	this->NoofBin = noofBin;
	this->TotalNoofObject = 0;
}

void CHistogram::SetFileName(std::string tranningFileName,std::string testFileName)
{
	this->TranningFileName = tranningFileName;
	this->TestFileName = testFileName;
}
eErrorType CHistogram::HistogramCreateBin()
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
		std::map<double,SHistogramDistribution>::iterator mapItr = mapHistogramClassification.find(ClassValue); 
		if(mapItr == mapHistogramClassification.end())
		{
			SHistogramDistribution HisDisObj;	
			HisDisObj.Probability = 0;
			HisDisObj.NoofEntries = 1;
			int DimensionIndex = 1;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
				SHistogramDimension DimensionObj;
				DimensionObj.SmallestNumber = *Vecitr;
				DimensionObj.LargestNumber = *Vecitr;
				for(int index = 0; index< this->NoofBin;++index)
				{
					DimensionObj.BinFrequency.push_back(0);
					DimensionObj.BinProbability.push_back(0);
				}
				HisDisObj.Dimension.push_back(DimensionObj);
				DimensionIndex++;
			}
			mapHistogramClassification.insert(std::pair<double,SHistogramDistribution>(ClassValue,HisDisObj));
		}
		else
		{
			mapItr->second.NoofEntries++;
			std::vector<SHistogramDimension>::iterator itrHisDimen = mapItr->second.Dimension.begin();
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
				if(itrHisDimen != mapItr->second.Dimension.end())
				{
					if(*Vecitr < itrHisDimen->SmallestNumber)
					{
						itrHisDimen->SmallestNumber = *Vecitr;
					}
					if(*Vecitr > itrHisDimen->LargestNumber)
					{
						itrHisDimen->LargestNumber = *Vecitr;
					}
					itrHisDimen++;
				}
				else
				{
					SHistogramDimension DimensionObj;
					DimensionObj.SmallestNumber = *Vecitr;
					DimensionObj.LargestNumber = *Vecitr;
					for(int index = 0; index< this->NoofBin;++index)
					{
						DimensionObj.BinFrequency.push_back(0);
						DimensionObj.BinProbability.push_back(0);
					}
					mapItr->second.Dimension.push_back(DimensionObj);
				}
			}
		}
	}
	for(int index=0;index<this->Dimension;index++)
	{
		Smallest.push_back(DBL_MAX);
		Largest.push_back(DBL_MIN);
	}
	for(std::map<double,SHistogramDistribution>::iterator mapItr = mapHistogramClassification.begin();
		mapItr != mapHistogramClassification.end();++mapItr)
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
	

/*	for(std::map<double,SHistogramDistribution>::iterator mapItr = mapHistogramClassification.begin();
		mapItr != mapHistogramClassification.end();++mapItr)
	{
		
		for(int DimensionIndex = 0;DimensionIndex<this->Dimension;++DimensionIndex)
		{
			mapItr->second.Dimension[DimensionIndex].SmallestNumber = Smallest[DimensionIndex];
			mapItr->second.Dimension[DimensionIndex].LargestNumber = Largest[DimensionIndex];
		}
	}*/
	FileObj.CloseFile();
	return Error;
}

eErrorType CHistogram::HistogramProbabilityCalculation()
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
	//	std::cout<<"Class Value:"<<ClassValue<<std::endl;
		std::map<double,SHistogramDistribution>::iterator mapItr = mapHistogramClassification.find(ClassValue); 
		if(mapItr != mapHistogramClassification.end())
		{
			int DimensionIndex = 0;
			int BinIndex = 0;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
	//			std::cout<<"Data : "<<*Vecitr<<std::endl;
				double Lowest = mapItr->second.Dimension[DimensionIndex].SmallestNumber;
				double Largest = mapItr->second.Dimension[DimensionIndex].LargestNumber;
				double BinRange = (Largest - Lowest)/(this->NoofBin -3);
				if( 0.0001 > BinRange)
				{
					BinRange = 0.0001;
				}
				if(0 != BinRange)
				{
					for(int index = 0;index <this->NoofBin;++index)
					{
						double BinBoundLowest = Lowest + ( (index-2) * BinRange) + BinRange/2;
						double BinBoundHighest = Lowest + ( (index-1) * BinRange) + BinRange/2;
						if(index == 0)
						{
							BinBoundLowest = -DBL_MAX;
							BinBoundHighest = Lowest - BinRange/2;
						}
						if(index == 1)
						{
							BinBoundLowest = Lowest - BinRange/2;
							BinBoundHighest = Lowest + BinRange/2;
						}
						if(index == this->NoofBin-1)
						{
							BinBoundHighest = DBL_MAX;
						}
/*						std::cout<<"Class : "<<ClassValue<<std::endl;
						std::cout<<"Lowest : "<<Lowest<<std::endl;
						std::cout<<"Highest : "<<Largest<<std::endl;
						std::cout<<"BinRange : "<<BinRange<<std::endl;
						std::cout<<"Attribute : "<<DimensionIndex<<std::endl;*/
						if( BinBoundLowest <=  *Vecitr && *Vecitr < BinBoundHighest)
						{
							BinIndex = index;
				//			std::cout<<"Bin Index :"<<BinIndex<<std::endl;
						}
					}
					mapItr->second.Dimension[DimensionIndex].BinFrequency[BinIndex]++;
	//				std::cout<<"class :"<<mapItr->first<<"Data :"<<*Vecitr<<"Frequency in bin "<<BinIndex<<" : "<<mapItr->second.Dimension[DimensionIndex].BinFrequency[BinIndex]<<std::endl;
				}
				else
				{
					mapItr->second.Dimension[DimensionIndex].BinFrequency[0]++;
				}
				DimensionIndex++;	
			}
		}
	}
	CalculateProbability();
	for(std::map<double,SHistogramDistribution>::iterator mapItr = mapHistogramClassification.begin();
			mapItr != mapHistogramClassification.end();++mapItr)
	{

		for(int DimensionIndex = 0;DimensionIndex < this->Dimension;DimensionIndex++)
		{
			double Lowest = mapItr->second.Dimension[DimensionIndex].SmallestNumber;
			double Largest = mapItr->second.Dimension[DimensionIndex].LargestNumber;
			double BinRange = (Largest - Lowest)/(this->NoofBin -3);
			for(int BinIndex = 0;BinIndex <this->NoofBin;++BinIndex)
			{
				std::cout<<"Class "<<(int)mapItr->first<<", attribute "<<DimensionIndex;
				double Denominator;
				if(BinRange < 0.0001)
				{
					BinRange = 0.0001;
				}
				if( 0 != BinRange)
				{
					Denominator = mapItr->second.NoofEntries * BinRange;
					if(0!=mapItr->second.Dimension[DimensionIndex].BinFrequency[BinIndex])
					{
						mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex] = 
							mapItr->second.Dimension[DimensionIndex].BinFrequency[BinIndex] / Denominator;
					}
				}
				else
				{
					if(0!=mapItr->second.Dimension[DimensionIndex].BinFrequency[BinIndex])
					{
						mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex] = 1;
					}
					
				}
				std::cout<<", bin "<<BinIndex <<", P(bin | class) = "<<std::fixed<<std::setprecision(2)
						<<mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex]
					/*	<<", Class Probability :"<<mapItr->second.Probability*/<<std::endl;
			}
		}
	} 
	FileObj.CloseFile();
	return Error;
}

eErrorType CHistogram::HistogramClassification()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
	char delit[] = " \t";
	int ObjectID =0;
	double AverageAccuracy = 0;
	FileObj.OpenFile(TestFileName);
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
		int PredictedClass = (int)ClassValue;
		double PredictedClassCount = 0;
		std::map<double,double> ConditionalProbability;
		double DenomeratorProbabilityMultiplication = 1;
		std::vector<double> TotalProbability;
		double CurrentNumerator = 0;
		double HistogramProbability = 0;
		double NewDenomirator = 0;
		TotalProbability.reserve(LineData.size()-1);
		TotalProbability.clear();
		for(int index = 0;index<LineData.size()-1;index++)
		{
			TotalProbability.push_back(0);
		}
		ConditionalProbability.clear();
		for(std::map<double,SHistogramDistribution>::iterator mapItr = mapHistogramClassification.begin();
			mapItr != mapHistogramClassification.end();++mapItr)
		{
			int DimensionIndex = 0;
			int BinIndex = 0;
			CurrentNumerator = mapItr->second.Probability;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{
				BinIndex = 0;
				double Lowest = mapItr->second.Dimension[DimensionIndex].SmallestNumber;
				double Largest = mapItr->second.Dimension[DimensionIndex].LargestNumber;
				double BinRange = (Largest - Lowest)/(this->NoofBin -3);
				if(BinRange < 0.0001)
				{
					BinRange = 0.0001;
				}
				if(0 != BinRange)
				{
					double BinBoundLowest =0;
					double BinBoundHighest = 0;
					for(int index = 0;index <this->NoofBin;++index)
					{
						BinBoundLowest = Lowest + ( (index-2) * BinRange) + BinRange/2;
						BinBoundHighest = Lowest + ( (index-1) * BinRange) + BinRange/2;
						if(index == 0)
						{
							BinBoundLowest = -DBL_MAX;
							BinBoundHighest = Lowest - BinRange/2;
						}
						if(index == 1)
						{
							BinBoundLowest = Lowest - BinRange/2;
							BinBoundHighest = Lowest + BinRange/2;
						}
						if(index == this->NoofBin-1)
						{
							BinBoundHighest = DBL_MAX;
						}
				/*				std::cout<<"Class : "<<mapItr->first;
								std::cout<<",Data : "<<*Vecitr;
								std::cout<<",Dimension : "<<DimensionIndex;
								std::cout<<",BinIndex : "<<BinIndex;
								std::cout<<",Lowest Range :"<<BinBoundLowest;
								std::cout<<",Highest Range :"<<BinBoundHighest<<std::endl;*/
						if( BinBoundLowest <=  *Vecitr && *Vecitr < BinBoundHighest)
						{
							BinIndex = index ;
		//					std::cout<<"Class : "<<mapItr->first<<",BIn Index : "<<BinIndex<<",Dimension :"<<DimensionIndex<<",Data :"<<*Vecitr<<",MIn : "<<BinBoundLowest<<",Max : "<<BinBoundHighest<<std::endl;
/*							if(0 == BinIndex)
							{
								std::cout<<"Class : "<<mapItr->first;
								std::cout<<",Data : "<<*Vecitr;
								std::cout<<",Dimension : "<<DimensionIndex;
								std::cout<<",BinIndex : "<<BinIndex;
								std::cout<<",Lowest Range :"<<BinBoundLowest;
								std::cout<<",Highest Range :"<<BinBoundHighest<<std::endl;
							}
							if((this->NoofBin-1) == BinIndex)
							{
								std::cout<<"Class : "<<mapItr->first;
								std::cout<<",Data : "<<*Vecitr;
								std::cout<<",Dimension : "<<DimensionIndex;
								std::cout<<",BinIndex : "<<BinIndex;
								std::cout<<",Lowest Range :"<<BinBoundLowest;
								std::cout<<",Highest Range :"<<BinBoundHighest<<std::endl;
							}*/
						}
					}
/*					if(0 ==mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex])
					{
						std::cout<<"Zero Probability :";
						std::cout<<"Class : "<<mapItr->first;
						std::cout<<",Data : "<<*Vecitr;
						std::cout<<",Dimension : "<<DimensionIndex;
						std::cout<<",BinIndex : "<<BinIndex;
						std::cout<<",Lowest Range :"<<BinBoundLowest;
						std::cout<<",Highest Range :"<<BinBoundHighest<<std::endl;
					}*/
//					std::cout<<"CUrrent Nurerator :"<<CurrentNumerator<<" * "<<mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex]<<" : ";
					CurrentNumerator = CurrentNumerator 
								* mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex];	
		//			std::cout<<CurrentNumerator<<std::endl;
				}
				else
				{
//					std::cout<<"Lowest : "<<Lowest<<", Data :"<<*Vecitr<<std::endl;
					if(Lowest == *Vecitr)
					{
						CurrentNumerator = CurrentNumerator * 1;
					}
					else
					{
//						std::cout<<"Hello Lowest"<<std::endl;
						CurrentNumerator = CurrentNumerator * 0;
					}
				}
//				std::cout<<"Class : "<<mapItr->first<<"Data : "<<*Vecitr<<"Bin Index :"<<BinIndex;
//				std::cout<<" Bin Probability"<<mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex]<<std::endl;
				TotalProbability[DimensionIndex]=TotalProbability[DimensionIndex] + 
					mapItr->second.Dimension[DimensionIndex].BinProbability[BinIndex]*(mapItr->second.Probability);
//				std::cout<<"Total Probability After addition:"<<TotalProbability[DimensionIndex]<<std::endl;
//				std::cout<<"Class Probability :"<<(mapItr->second.Probability)<<std::endl;
				DimensionIndex++;	
			}
			NewDenomirator = NewDenomirator + CurrentNumerator;
			ConditionalProbability.insert(std::pair<double,double>(mapItr->first,CurrentNumerator));
//			break;
		}
//		std::cout<<"Denominator :"<<DenomeratorProbabilityMultiplication<<std::endl;
//		std::cout<<"Total Prob"<<std::endl;
		for(std::vector<double>::iterator itrToProb = TotalProbability.begin();itrToProb!=TotalProbability.end();++itrToProb)
		{
//			std::cout<<*itrToProb;
			DenomeratorProbabilityMultiplication = DenomeratorProbabilityMultiplication * *itrToProb;	
		}
//		std::cout<<std::endl<<"Denominator :"<<DenomeratorProbabilityMultiplication<<std::endl;
		for(std::map<double,double>::iterator itrCdProb = ConditionalProbability.begin();itrCdProb!=ConditionalProbability.end();
				++itrCdProb)
		{
		//	std::cout<<"Class : "<<itrCdProb->first<<"Numerator "<<itrCdProb->second<<std::endl;
			//double CurrentHisProb = itrCdProb->second/DenomeratorProbabilityMultiplication;
		//	std::cout<<"Total Denominator : "<<NewDenomirator<<std::endl;
			double CurrentHisProb = 0;
			if(0!=NewDenomirator)
			{
				CurrentHisProb = itrCdProb->second/NewDenomirator;
			//	std::cout<<"Hello world"<<std::endl;
			//	std::cout<<"Numerator :"<<itrCdProb->second<<std::endl;
			}
			else
			{
				CurrentHisProb = 1/10;
			}
//			std::cout<<"Current HisProb :"<<CurrentHisProb<<std::endl;
			if(CurrentHisProb > HistogramProbability)
			{
				HistogramProbability = CurrentHisProb;	
				PredictedClass = (int)itrCdProb->first;
				PredictedClassCount = 1;
//				std::cout<<"Predicted CLass: greater"<<PredictedClassCount<<std::endl;
			}
			else if(CurrentHisProb == HistogramProbability)
			{
				if(ClassValue == itrCdProb->first)
				{
					PredictedClass = ClassValue;
				}
			//	PredictedClassCount = 1;
	
				PredictedClassCount++;
//				std::cout<<"Predicted CLass equal:"<<PredictedClassCount<<std::endl;
//				std::cout<<"Predicted CLass:"<<std::endl;
			}
		}
		double accuracy = 0;	
		if(ClassValue == PredictedClass)
		{
			accuracy = 1/double(PredictedClassCount);
			AverageAccuracy = AverageAccuracy + accuracy;
		}
//		std::cout<<"Prob : "<<HistogramProbability<<std::endl;
		printf("ID=%5d, predicted=%3d, probability = %.4lf, true=%3d, accuracy=%4.2lf\n", 
					ObjectID,PredictedClass, HistogramProbability, (int)ClassValue, accuracy);
		ObjectID++;
/*		if(1==ObjectID)
		{
			break;
		}*/
	}
	AverageAccuracy = AverageAccuracy / ObjectID;
	printf("classification accuracy=%6.4lf\n", AverageAccuracy);
//	std::cout<<"Object count :"<<ObjectID<<std::endl;
	FileObj.CloseFile();
	return Error;
}
eErrorType CHistogram::CalculateProbability()
{
	eErrorType Error = SUCCESS;
	for(std::map<double,SHistogramDistribution>::iterator mapItr = mapHistogramClassification.begin();
			mapItr != mapHistogramClassification.end();++mapItr)
	{
		if( 0 < TotalNoofObject )
		{
			mapItr->second.Probability = (double)mapItr->second.NoofEntries / (double)TotalNoofObject; 
		}
	}
	return Error;
}
