#ifndef UTILITY_H
#define UTILITY_H
#include<vector>

struct GaussianDestribution
{
	std::vector<double> SumDimension;
	std::vector<double> Variance;
	int NumberofEntries;
	double Probability;

};

enum eErrorType
{
	SUCCESS,
	FILEOPENFAIL,
	FILEEXCEPTION,
	ENDOFFILE,
	FAIL
};

struct SHistogramDimension
{
	double SmallestNumber;
	double LargestNumber;
	std::vector<int> BinFrequency;
	std::vector<double> BinProbability;
};

struct SHistogramDistribution
{
	std::vector<SHistogramDimension> Dimension;
	double Probability;
	int NoofEntries;
};

struct SMixtureDimension
{
	double SmallestNumber;
	double LargestNumber;
	int ProbabilityIndex;
	std::vector<double> Mean;
	std::vector<double> StandardDeviation;
	std::vector<double> Weight;
	std::vector<double> MixtureProbability;
	std::vector<double> MixtureIndivisualProbability;
	std::vector<double> MixtureProbabilityMeanValue;	//Pij * Xj
	std::vector<double> MixtureProbabilityVarianceValue;	//pij(xj -Uj)^2
};

struct SMixtureDistribution
{
	std::vector<SMixtureDimension> Dimension;
	double Probability;
	int NoofEntries;
};


#endif

