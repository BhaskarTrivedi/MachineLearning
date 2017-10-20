#ifndef UTILITY_H
#define UTILITY_H
#include<vector>
#include<map>


enum eErrorType
{
	SUCCESS,
	FILEOPENFAIL,
	FILEEXCEPTION,
	ENDOFFILE,
	FAIL
};


struct TreeNode
{
	int NodeId;
	int FeatureId;
	double Threshold;
	double IGain;
	std::map<double,double> *mapDistribution;
	TreeNode *Left;
	TreeNode *Right;
	
};

enum eTreeType
{
	OPTIMIZED,
	RANDOMIZED,
	FOREST3,
	FOREST15
};

enum eFileType
{
	TRANNING,
	TEST
};

#endif

