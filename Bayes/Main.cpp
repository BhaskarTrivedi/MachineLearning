#include"CFileReading.h"
#include"Utility.h"
#include"CGaussian.h"
#include"CHistogram.h"
#include"CMixture.h"
#include<iomanip>
#include<iostream>
#include<string>
#include<math.h>
#include<stdlib.h>

void GaussianClassification(std::string TranningFileName,std::string TestFileName);
void HistogramClassification(std::string TranningFileName,std::string TestFileName,std::string noOfBin);
void MixtureClassification(std::string TranningFileName,std::string TestFileName,std::string noOfMixture);

int main(int argc,char* argv[])
{
	if(argc < 4)
	{
		std::cout<<"Too few parameter!! "<<std::endl;
		return 0;
	}
	std::string Classification = argv[3];
	if(!Classification.compare("gaussians"))
	{
		GaussianClassification(argv[1],argv[2]);
	}
	else if(!Classification.compare("histograms"))
	{
		HistogramClassification(argv[1],argv[2],argv[4]);
	}
	else if(!Classification.compare("mixtures"))
	{
		MixtureClassification(argv[1],argv[2],argv[4]);
	}
	return 0;
}


void GaussianClassification(std::string TranningFileName,std::string TestFileName)
{
	CGaussian2D GaussianObj;
	eErrorType Error = SUCCESS;
	GaussianObj.SetFileName(TranningFileName,TestFileName);
	Error = GaussianObj.CalculateMean();
	Error = GaussianObj.CalculateVariance();
	std::map<double,GaussianDestribution> mapGaussianData;
	mapGaussianData = GaussianObj.GetGaussianData();
	for(std::map<double,GaussianDestribution>::iterator mapitr = mapGaussianData.begin();mapitr != mapGaussianData.end();++mapitr)
        {
                std::vector<double>::iterator vecVarianceItr = mapitr->second.Variance.begin();
                int Dimension = 0;
                for(std::vector<double>::iterator vecitr = mapitr->second.SumDimension.begin();vecitr != mapitr->second.SumDimension.end();
                        ++vecitr)
                {
                        double mean = *vecitr / mapitr->second.NumberofEntries;
                        std::cout<<"Class "<<(int)mapitr->first<<", attribute "<<Dimension<<std::fixed<<std::setprecision(2)<<", mean = "<<mean;
			double StandardDeviation;
			if( 0.0001 > *vecVarianceItr )
			{
				StandardDeviation = sqrt(0.0001);
			}
			else
			{
				StandardDeviation = sqrt(*vecVarianceItr);
			}
			std::cout<<", std : "<<StandardDeviation<</*"Variance :"<<*vecVarianceItr<<*/std::endl;
                	Dimension++;
                	vecVarianceItr++;
                }
        }
	Error = GaussianObj.NaiveBayesGaussian();
}

void HistogramClassification(std::string TranningFileName,std::string TestFileName,std::string noOfBin)
{
	int NoofBin = 1;	
	char delit[] = "<>";
	char *der = (char *)noOfBin.c_str();
	char* token = std::strtok(der,delit);
	while(token!=NULL)
	{
		NoofBin = atoi(token);	
		token = std::strtok(NULL,delit);
	}
	if(0>= NoofBin)
	{
		NoofBin = 1;
	}
	CHistogram HistogramObj(NoofBin);
	HistogramObj.SetFileName(TranningFileName,TestFileName);
	HistogramObj.HistogramCreateBin();
	HistogramObj.HistogramProbabilityCalculation();
	HistogramObj.HistogramClassification();
}

void MixtureClassification(std::string TranningFileName,std::string TestFileName,std::string noOfMixture)
{
	int NoofMix = 1;	
	char delit[] = "<>";
	char *der = (char *)noOfMixture.c_str();
	char* token = std::strtok(der,delit);
	while(token!=NULL)
	{
		NoofMix = atoi(token);	
		token = std::strtok(NULL,delit);
	}
	if(0 >= NoofMix)
	{
		NoofMix = 1;
	}
	CMixture CMixtureObj(NoofMix);
	CMixtureObj.SetFileName(TranningFileName,TestFileName);
	CMixtureObj.CreateMixture();
//	CMixtureObj.Display();
	CMixtureObj.EMAlgorithm();
//	std::cout<<"After EM Algorithm:"<<std::endl;
	CMixtureObj.Display();
	CMixtureObj.Classification();
}
