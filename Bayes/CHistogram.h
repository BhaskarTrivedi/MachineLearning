#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include"Utility.h"
#include<string>
#include<map>

class CHistogram
{
public:
	CHistogram(int NoOfBin);
	void SetFileName(std::string TranningFileName,std::string TestFileName);
	eErrorType HistogramClassification();
	eErrorType HistogramProbabilityCalculation();
	eErrorType HistogramCreateBin();
private:
	eErrorType CalculateProbability();
	std::map<double,SHistogramDistribution> mapHistogramClassification;	
	int TotalNoofObject;
	std::string TranningFileName;
	std::string TestFileName;
	int NoofBin;
	std::vector<double> LineData;
	int Dimension;
	std::vector<double> Smallest;
	std::vector<double> Largest;
};


#endif
