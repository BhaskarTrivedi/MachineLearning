#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include"CFileReading.h"
#include<string>
#include<vector>

class CLinearRegression
{
public:
	CLinearRegression();
	eErrorType FileReading(std::string FileName);
	eErrorType LinearRegression(int Degree,double lamda);
	void Display();
private:
	void CalculatePhi();
	double** MatrixMultiplication(double **Mat1,int row1,int col1,double **Mat2,int row2,int col2);
	double** MatrixAddition(double **Mat1,int row1,int col1,double **Mat2,int row2,int col2);
	double** MatrixTranspose(double **Mat1,int row1,int col1);
	double** MatrixScalarMultiplication(double **Mat1,int row1,int col1,double Value);
	double** AllocateMemory(int row1,int col1);
	double** CalculateIdentityMatrix();
	double** MatrixScalarDivision(double **Mat1,int row1,int col1,double Value);
	double MatrixDeterminate(double** Mat1,int row);
	void MatrixCofactor(double** Mat1,double **Temp,int row,int col,int size);
	void MatrixAdjoint(double** Mat1,double **Temp);
	void MatrixInverse(double** Mat1,double **InverseMat);
	double Lamda;
	double **PhiTranspose;
	double **Phi;
	double **Target;
	double **Weight;
	double **IdentityMatrix;
	int Degree;
	std::string FileName;
	std::vector<double> Input;
	std::vector<double> Output;
	int NoOfTrainingData;
};

#endif
