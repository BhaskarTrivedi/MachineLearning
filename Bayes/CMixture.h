#ifndef CMIXTURE_H
#define CMIXTURE_h
#include"Utility.h"
#include<map>
#include<string>

class CMixture
{
public:
	CMixture(int NoMixture);
	eErrorType CreateMixture();
	eErrorType EMAlgorithm();
	void SetFileName(std::string TranningFileName,std::string TestFileName);
	void Display();
	eErrorType Classification();
private:
	eErrorType CalculateClassProbability();
	eErrorType VarianceCalculation();
	eErrorType MeanCalculation();
	eErrorType WeightCalculation();
	double GaussianValue(double value,double mean,double stDev);
	int TotalNoofObject;
	std::string TranningFileName;
	std::string TestFileName;
	std::vector<double> LineData;
	std::map<double,SMixtureDistribution> mapMixtureClassification;
	int NoofMixture;
	std::vector<double> Smallest;
	std::vector<double> Largest;
	int Dimension;
};


#endif
