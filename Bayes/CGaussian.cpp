#include"CGaussian.h"
#include"CFileReading.h"
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<limits.h>

void CGaussian2D::SetFileName(std::string tranningFileName,std::string testFileName)
{
	this->TranningFileName = tranningFileName;
	this->TestFileName = testFileName;
}

eErrorType CGaussian2D::CalculateMean()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
	char delit[] = " \t";
	FileObj.OpenFile(TranningFileName);
	TotalObject = 0;
	this->Dimension = 0;
	while( SUCCESS == FileObj.GetLine(Line))
	{
		char *der = (char *)Line.c_str();
		char* token = std::strtok(der,delit);
		LineData.clear();
		++TotalObject;
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
		std::map<double,GaussianDestribution>::iterator mapitr = mapGaussianDistribution.find(ClassValue);
		if(mapitr == mapGaussianDistribution.end())
		{
			GaussianDestribution GDes;
			int DimensionIndex = 1;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{	
				GDes.SumDimension.push_back(*Vecitr);
				GDes.Variance.push_back(0);
				DimensionIndex++;
			}
			while(DimensionIndex < Dimension)
			{
				GDes.SumDimension.push_back(0);
				GDes.Variance.push_back(0);
				DimensionIndex++;
			}
			GDes.NumberofEntries = 1;
			mapGaussianDistribution.insert(std::pair<double,GaussianDestribution>(ClassValue,GDes));
		}
		else
		{
			std::vector<double>::iterator vecMeanItr = mapitr->second.SumDimension.begin();	
			int SumIndex = 0;
			for(std::vector<double>::iterator Vecitr = LineData.begin();Vecitr!=LineData.end() -1;++Vecitr)
			{	
				if(vecMeanItr != mapitr->second.SumDimension.end() )
				{
					
					mapitr->second.SumDimension[SumIndex] = mapitr->second.SumDimension[SumIndex] + *Vecitr;	
					SumIndex++;
				}	
				else
                                {
                                	mapitr->second.SumDimension.push_back(*Vecitr);
                                }
				++vecMeanItr;
			}
			mapitr->second.NumberofEntries++;	
		}
	}
	FileObj.CloseFile();
	Error = CalculateProbability();
	return Error;
}
eErrorType CGaussian2D::CalculateVariance()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	std::string Line;
	char delit[] = " \t";
	FileObj.OpenFile(TranningFileName);
	while( SUCCESS == FileObj.GetLine(Line))
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
		double ClassValue = LineData.back();
		std::map<double,GaussianDestribution>::iterator mapitr = mapGaussianDistribution.find(ClassValue);
		int VarianceIndex = 0;
		if(mapitr != mapGaussianDistribution.end())
		{
			std::vector<double>::iterator itrVariance = mapitr->second.Variance.begin();	
			for(std::vector<double>::iterator itrVec = LineData.begin();itrVec != LineData.end()-1;++itrVec)
                        {
                        	if(itrVariance != mapitr->second.Variance.end())
                                {
                                	mapitr->second.Variance[VarianceIndex] = mapitr->second.Variance[VarianceIndex] +
                                		( *itrVec - mapitr->second.SumDimension[VarianceIndex]/mapitr->second.NumberofEntries ) *
                                                ( *itrVec - mapitr->second.SumDimension[VarianceIndex]/mapitr->second.NumberofEntries );
                                                        VarianceIndex++;
                                                        itrVariance++;
                        	}
                	}
                        if(itrVariance != mapitr->second.Variance.end())
                        {
                        	while(itrVariance != mapitr->second.Variance.end())
                                {
                                	mapitr->second.Variance[VarianceIndex] = mapitr->second.Variance[VarianceIndex] +
                                        	(mapitr->second.SumDimension[VarianceIndex]/mapitr->second.NumberofEntries ) *
                                                (mapitr->second.SumDimension[VarianceIndex]/mapitr->second.NumberofEntries );
                                        	VarianceIndex++;
                                       		itrVariance++;
                                }
                         }
		}
	}
	for(std::map<double,GaussianDestribution>::iterator mapitr = mapGaussianDistribution.begin();
				mapitr != mapGaussianDistribution.end();++mapitr)
	{
		int index = 0;
		for(std::vector<double>::iterator VecitrVariance = mapitr->second.Variance.begin();
                                        VecitrVariance != mapitr->second.Variance.end(); ++VecitrVariance)
                {

			if(0 != mapitr->second.Variance[index])
			{
                		mapitr->second.Variance[index] = mapitr->second.Variance[index] /
                        		(mapitr->second.NumberofEntries - 1 );
			}
			index++;
                }
	}

	FileObj.CloseFile();
	return Error;
}

std::map<double,GaussianDestribution> CGaussian2D::GetGaussianData()
{
	return mapGaussianDistribution;
}


eErrorType CGaussian2D::CalculateProbability()
{
	eErrorType Error = SUCCESS;
	for(std::map<double,GaussianDestribution>::iterator mapitr = mapGaussianDistribution.begin();
				mapitr != mapGaussianDistribution.end();++mapitr)
	{
		if( 0 < TotalObject )
		{
			mapitr->second.Probability = (double)mapitr->second.NumberofEntries / (double)TotalObject; 
		}
	}
	return Error;
}

eErrorType CGaussian2D::NaiveBayesGaussian()
{
	eErrorType Error = SUCCESS;
	CFileReading FileObj;
	double AverageAccuracy = 0;
	std::string Line;
	char delit[] = " \t";
	FileObj.OpenFile(TestFileName);
	int ObjectID =0;
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
		double GaussianProbability = 0;
//		double CalculatedNumerator = 1;
		double CurrentGaussianProbability  = 0;
		int PredictedClass = (int)ClassValue;
		double PredictedClassCount = 0;
		double CurrentNumerator = 0;
		double NewDenominator = 0;
		double DenomeratorProbabilityMultiplication = 1;
		std::vector<double> TotalProbability;
		TotalProbability.reserve(LineData.size()-1);
		TotalProbability.clear();
		for(int index = 0;index<LineData.size()-1;index++)
		{
			TotalProbability.push_back(0);
		}
		std::map<double,double> ConditionalProbability;
		ConditionalProbability.clear();
		for(std::map<double,GaussianDestribution>::iterator mapitr = mapGaussianDistribution.begin();mapitr != mapGaussianDistribution.end();++mapitr)
		{
			int index = 0;
			CurrentNumerator = mapitr->second.Probability;
	//		CurrentNumerator = 1;
			for(std::vector<double>::iterator itrLine = LineData.begin();itrLine<LineData.end()-1;++itrLine)
			{
				if( 0.0001 > mapitr->second.Variance[index])
				{
					mapitr->second.Variance[index] = 0.0001;
				}
				if( 0 != mapitr->second.Variance[index])
				{
					double pi = 3.1415926535897932384626;
					double gauNume = 2*mapitr->second.Variance[index]*pi;
					double sqrGauNume = sqrt(gauNume);
		//			std::cout<<"SqyGauNume :"<<sqrGauNume<<std::endl;
			//j		std::cout<<*itrLine<<std::endl;
			//		std::cout<<mapitr->second.Variance[index]<<std::endl;
					double ExpPower=-1*(*itrLine - mapitr->second.SumDimension[index]/mapitr->second.NumberofEntries) * 							(*itrLine - mapitr->second.SumDimension[index]/mapitr->second.NumberofEntries);
					
					if(ExpPower !=0 )
					{
						ExpPower = ExpPower/(2*mapitr->second.Variance[index]);
					}
		//		std::cout<<"ExpPower :"<<ExpPower<<std::endl;
					double ExpPowerValue = exp(ExpPower);
		//			std::cout<<"ExpPowerValue :"<<ExpPowerValue<<std::endl;
					CurrentGaussianProbability = ExpPowerValue / sqrGauNume;
		//			std::cout<<ExpPowerValue<<" / "<<sqrGauNume<<std::endl;
//				std::cout<<"Class :"<<mapitr->first<<",Data : "<<*itrLine<<",Current Gaussian Probability :"<<CurrentGaussianProbability<<std::endl;
				}
				else
				{
					if(*itrLine == mapitr->second.SumDimension[index]/mapitr->second.NumberofEntries)
					{
						CurrentGaussianProbability = .99;
					}
					else
					{
						CurrentGaussianProbability = 0.01;
					}
				}
			//	std::cout<<"Class :"<<mapitr->first<<",Data :"<<*itrLine<<" Current Gaussian Probability"<<CurrentGaussianProbability<<std::endl;
//				std::cout<<"Current NUmerator :"<<CurrentNumerator<<std::endl;
//				std::cout<<"Updated numerator : "<<CurrentNumerator<<" * "<<CurrentGaussianProbability<<std::endl;
				CurrentNumerator = CurrentNumerator * CurrentGaussianProbability;	
//				std::cout<<" : "<<CurrentNumerator<<std::endl;
			//	std::cout<<"Class :"<<mapitr->first<<",Data :"<<*itrLine<<" before Total Probability: "<<TotalProbability[index]<<std::endl;
				TotalProbability[index]=TotalProbability[index]+CurrentGaussianProbability*(mapitr->second.Probability);
			//	std::cout<<"Class :"<<mapitr->first<<",Data :"<<*itrLine<<" After Addition Total Probability: "<<TotalProbability[index]<<std::endl;
		//		std::cout<<"Current Total Prob "<<index<<" : "<<TotalProbability[index]<<std::endl;	
				index++;
			}
		//	std::cout<<std::endl<<std::endl<<"Current Class :"<<mapitr->first<<std::endl<<std::endl;
		//	std::cout<<"Total current Numerator :"<<CurrentNumerator<<std::endl<<std::endl;
		//	std::cout<<"CLass :"<<mapitr->first<<",Total Denominator before:"<<NewDenominator<<std::endl<<std::endl;
//			std::cout<<NewDenominator<<" + "<<CurrentNumerator<<std::endl;
			NewDenominator = NewDenominator + CurrentNumerator;
//			std::cout<<"CLass :"<<mapitr->first<<",Total Denominator :"<<NewDenominator<<std::endl<<std::endl;
			ConditionalProbability.insert(std::pair<double,double>(mapitr->first,CurrentNumerator));
		}
	//	std::cout<<"Predicted Class Count :"<<PredictedClassCount<<std::endl;
//		std::cout<<"Size of total Prob"<<TotalProbability.size()<<std::endl;
		for(std::vector<double>::iterator itrToProb = TotalProbability.begin();itrToProb!=TotalProbability.end();++itrToProb)
		{
		//	std::cout<<"Total Prob : "<<*itrToProb<<std::endl;
			DenomeratorProbabilityMultiplication = DenomeratorProbabilityMultiplication * *itrToProb;	
		}
//		std::cout<<"Current Denomirator"<<DenomeratorProbabilityMultiplication<<std::endl;
		for(std::map<double,double>::iterator itrCdProb = ConditionalProbability.begin();itrCdProb!=ConditionalProbability.end();
				++itrCdProb)
		{
//			std::cout<<"Class : "<<itrCdProb->first<<" Class Numerator : "<<itrCdProb->second<<std::endl;
			//double CurrentGaProb = itrCdProb->second/DenomeratorProbabilityMultiplication;
			double CurrentGaProb = 0;
			if(0!=NewDenominator)
			{
				CurrentGaProb = itrCdProb->second/NewDenominator;
			}
			else
			{
				CurrentGaProb = 1/10;
			}
		//	std::cout<<"Class : "<<itrCdProb->first<<" Gaussian Probability : "<<CurrentGaProb<<std::endl;
			if(CurrentGaProb > GaussianProbability)
			{
				GaussianProbability = CurrentGaProb;	
				PredictedClass = (int)itrCdProb->first;
				PredictedClassCount = 1;
//				std::cout<<"Class :"<<itrCdProb->first<<"PredictedClassCount :"<<PredictedClassCount<<std::endl;
			}
			//else if(CurrentNumerator == GaussianProbability)
			else if(CurrentGaProb == GaussianProbability)
			{
				if(ClassValue == itrCdProb->first)
				{
					PredictedClass = ClassValue;
				}
				PredictedClassCount++;
//				std::cout<<"Class :"<<itrCdProb->first<<"PredictedClassCount :"<<PredictedClassCount<<std::endl;
			}
		}
		double accuracy = 0;	
		if(ClassValue == PredictedClass)
		{
			accuracy = 1/double(PredictedClassCount);
			AverageAccuracy = AverageAccuracy + accuracy;
		}
		printf("ID=%5d, predicted=%3d, probability = %.4lf, true=%3d, accuracy=%4.2lf\n", 
					ObjectID,PredictedClass, GaussianProbability, (int)ClassValue, accuracy);
		ObjectID++;
	}
	AverageAccuracy = AverageAccuracy / ObjectID;
	printf("classification accuracy=%6.4lf\n", AverageAccuracy);
//	std::cout<<"Object count :"<<ObjectID<<std::endl;
	FileObj.CloseFile();
	return Error;
}

