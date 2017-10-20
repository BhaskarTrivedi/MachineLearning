#ifndef CGAUSSIAN2D_H
#define CGAUSSIAN2D_H
#include"Utility.h"
#include<string>
#include<map>
#include<vector>


class CGaussian2D
{
public:
	void SetFileName(std::string TranningFileName,std::string TestFileName);
	eErrorType CalculateMean();
	eErrorType CalculateVariance();
	eErrorType NaiveBayesGaussian();
	std::map<double,GaussianDestribution> GetGaussianData();

private:
	eErrorType CalculateProbability();
	std::string TranningFileName;
	std::string TestFileName;
	std::map<double,GaussianDestribution> mapGaussianDistribution;
	std::vector<double> LineData;
	int Dimension;
	int TotalObject;
};

#endif
