#include"CLinearRegression.h"
#include<math.h>
#include<stdlib.h>
#include<iostream>
#include<stdlib.h>
#include<iomanip>

CLinearRegression::CLinearRegression()
{
	Weight = AllocateMemory(3,1);
	for(int row=0;row<3;row++)
	{
		Weight[row][0] = 0;
	}
	Degree = 0;
	Lamda = 0;
	NoOfTrainingData = 0;
}
eErrorType CLinearRegression::LinearRegression(int degree,double lamda)
{
	eErrorType Error = SUCCESS;
	Degree =  degree;
	Lamda = lamda;
	double **LamdaIdentityMatrix = NULL;
	CalculatePhi();
	double** PhiTransposePhiMultiplication=MatrixMultiplication(PhiTranspose,Degree+1,NoOfTrainingData,Phi,NoOfTrainingData,Degree+1);
	double** LamdaPhiAddition;
/*	std::cout<<"PhiTranspose * Phi :"<<std::endl;
	for(int row=0;row<Degree+1;row++)
	{
		for(int col=0;col<Degree+1;col++)
		{
			std::cout<<PhiTransposePhiMultiplication[row][col]<<" ";
		}
		std::cout<<std::endl;
	}*/
	if(lamda > 0 )
	{
		CalculateIdentityMatrix();
		LamdaIdentityMatrix = MatrixScalarMultiplication(IdentityMatrix,Degree+1,Degree+1,Lamda);
		LamdaPhiAddition = MatrixAddition(LamdaIdentityMatrix,Degree+1,Degree+1,PhiTransposePhiMultiplication,Degree+1,Degree+1);
/*		for(int row = 0;row<=Degree;row++)
		{
			for(int col=0;col<=Degree;col++)
			{
				std::cout<<LamdaIdentityMatrix[row][col]<<" ";
			}
			std::cout<<std::endl;
		}*/
	}
	else
	{
		LamdaPhiAddition = AllocateMemory(Degree+1,Degree+1);
		for(int row=0;row<Degree+1;row++)
		{
			for(int col=0;col<Degree+1;col++)
			{
				LamdaPhiAddition[row][col] = PhiTransposePhiMultiplication[row][col];
			}
		}
		
	}
	double **InverseMatrix = AllocateMemory(Degree+1,Degree+1);
	MatrixInverse(LamdaPhiAddition,InverseMatrix);
	double **InversePhiTranposeMultiplication = 
			MatrixMultiplication(InverseMatrix,Degree+1,Degree+1,PhiTranspose,Degree+1,NoOfTrainingData);
	double **MatWeight = MatrixMultiplication(InversePhiTranposeMultiplication,Degree+1,NoOfTrainingData,Target,NoOfTrainingData,1);
	for(int row = 0;row<Degree+1;row++)
	{
		Weight[row][0] = MatWeight[row][0];
	}
/*	double **arr1;
	double **arr2;
	arr1 = AllocateMemory(Degree+1,Degree+1);
	arr2 = AllocateMemory(3,5);
	int index = 1;
	for(int row=0;row<Degree+1;row++)
	{
		for(int col=0;col<Degree+1;col++)
		{
			arr1[row][col] = rand()%10;
		}
	}
	for(int row=0;row<Degree+1;row++)
	{
		for(int col=0;col<Degree+1;col++)
		{
			std::cout<<arr1[row][col]<<" ";
		}
		std::cout<<std::endl;
	}
	double **MatInverse = AllocateMemory(Degree+1,Degree+1);
	MatrixInverse(arr1,MatInverse);
	for(int row=0;row<Degree+1;row++)
	{
		for(int col=0;col<Degree+1;col++)
		{
			std::cout<<MatInverse[row][col]<<" ";
		}
		std::cout<<std::endl;
	}*/
//	MatrixMultiplication(arr1,2,3,arr2,3,5);
	return Error;
}
void CLinearRegression::CalculatePhi()
{
	Phi = AllocateMemory(NoOfTrainingData,Degree+1);
	for(int row = 0; row<NoOfTrainingData;row++)
        {
		for(int col=0;col<=Degree;col++)
		{
			double value = Input[row];
			Phi[row][col] = pow(value,col);
		}
	}
	PhiTranspose = MatrixTranspose(Phi,NoOfTrainingData,(Degree+1));
	/*for(int row = 0; row<NoOfTrainingData;row++)
        {
		for(int col=0;col<=Degree;col++)
		{
			std::cout<<Phi[row][col]<<" ";
		}
		std::cout<<std::endl;
	}*/
}
double** CLinearRegression::MatrixMultiplication(double **Mat1,int row1,int col1,double **Mat2,int row2,int col2)
{
	double **Result = NULL;
	if(col1 != row2)
	{
		return Result;
	}
	Result = AllocateMemory(row1,col2);
	for(int row = 0;row<row1;row++)
	{
		for(int col = 0;col<col2;col++)
		{
			Result[row][col] = 0;
			for(int index = 0;index<col1;index++)
			{
				Result[row][col] = Mat1[row][index]*Mat2[index][col] + Result[row][col];
			}
		}
	}
/*	for(int row = 0;row<row1;row++)
	{
		for(int col = 0;col<col2;col++)
		{
			std::cout<<Result[row][col]<<" ";
		}
		std::cout<<std::endl;
	}*/
	return Result;
}
double** CLinearRegression::MatrixAddition(double **Mat1,int row1,int col1,double **Mat2,int row2,int col2)
{
	double **Result = NULL;
	if(row1 == row2 && col1==col2)
	{
		Result = AllocateMemory(row1,col1);
		for(int row = 0; row <row1; row++)
		{
			for(int col = 0;col<col1;col++)
			{
				Result[row][col] = Mat1[row][col] + Mat2[row][col];
			}
		}
	}
	return Result;
}
double** CLinearRegression::MatrixTranspose(double **Mat1,int row1,int col1)
{
	double **Result = NULL;
	Result = AllocateMemory(col1,row1);
	for(int Row = 0 ;Row<row1;Row++)
	{
		for(int Col = 0;Col<col1;Col++)
		{
			Result[Col][Row] = Mat1[Row][Col];	
		}
	}
/*	for(int Row = 0 ;Row<col1;Row++)
	{
		for(int Col = 0;Col<row1;Col++)
		{
			std::cout<<Result[Row][Col]<<" ";
		}
		std::cout<<std::endl;
	}*/
	return Result;
}
double** CLinearRegression::MatrixScalarMultiplication(double **Mat1,int row1,int col1,double Value)
{
	double **Result = NULL;
	Result = AllocateMemory(row1,col1);
	for(int Row = 0 ;Row<row1;Row++)
	{
		for(int Col = 0;Col<col1;Col++)
		{
			Result[Col][Row] = Value * Mat1[Row][Col];	
		}
	}
	return Result;
}
double** CLinearRegression::MatrixScalarDivision(double **Mat1,int row1,int col1,double Value)
{
	double **Result = NULL;
	Result = AllocateMemory(row1,col1);
	for(int Row = 0 ;Row<row1;Row++)
	{
		for(int Col = 0;Col<col1;Col++)
		{
			Result[Col][Row] = (Mat1[Row][Col])/Value;	
		}
	}
	return Result;
}
eErrorType CLinearRegression::FileReading(std::string fileName)
{
	eErrorType Error = SUCCESS;
	this->FileName = fileName;
	CFileReading FileObj;
        std::string Line;
        char delit[] = " \t";
        FileObj.OpenFile(FileName);
        while( SUCCESS == FileObj.GetLine(Line))
        {
//		std::cout<<Line<<std::endl;
		char *der = (char *)Line.c_str();
		char* token = std::strtok(der,delit);
		bool inputflag = true;
                while(token!=NULL)
                {
                        double Value = atof(token);
			if(inputflag)
			{
				Input.push_back(Value);		
				inputflag = false;
			}
			else
			{
				Output.push_back(Value);
			}
                        token = std::strtok(NULL,delit);
                }
	}
	NoOfTrainingData = Output.size();
	Target = AllocateMemory(NoOfTrainingData,1);
	for(int index = 0; index < NoOfTrainingData;index++)
	{
		Target[index][0] = Output[index];	
	}
	
	/*for(int index = 0; index < NoOfTrainingData;index++)
	{
		std::cout<<Target[index]<<" ";	
	}
	std::cout<<std::endl;*/
	return Error;
}
double** CLinearRegression::AllocateMemory(int row1,int col1)
{
	double **Result = NULL;
	Result = (double**)malloc(sizeof(double*)*row1);
	for(int index = 0;index<row1;index++)
	{
		Result[index] = (double*)malloc(sizeof(double)*col1);
	}
	return Result;
}
double** CLinearRegression::CalculateIdentityMatrix()
{
	IdentityMatrix = AllocateMemory(Degree+1,Degree+1);
	for(int row = 0;row<=Degree;row++)
	{
		for(int col = 0;col<=Degree;col++)
		{
			if(col == row)
			{
				IdentityMatrix[row][col] = 1;
			}
			else
			{
				IdentityMatrix[row][col] = 0;
			}
		}
	}	
/*	for(int row = 0;row<=Degree;row++)
	{
		for(int col = 0;col<=Degree;col++)
		{
			std::cout<<IdentityMatrix[row][col]<<" ";
		}
		std::cout<<std::endl;
	}*/
}
double CLinearRegression::MatrixDeterminate(double** Mat1,int size)
{
	double detm = 0;
	if(size ==1)
	{
		return Mat1[0][0];
	}
/*	for(int row = 0;row<size;row++)
	{
		for(int col=0;col<size;col++)
		{
			std::cout<<Mat1[row][col]<<" ";
		}	
		std::cout<<std::endl;
	}*/
	double **TempMat = AllocateMemory(Degree+1,Degree+1);
	int sign = 1;
	for(int index = 0;index<size;index++)
	{
		MatrixCofactor(Mat1,TempMat,0,index,size);
		detm = detm + sign * Mat1[0][index] * MatrixDeterminate(TempMat,size - 1);
		sign = -sign;
	}
	return detm;
}
void CLinearRegression::MatrixCofactor(double** Mat1,double **Temp,int row1,int col1,int size)
{
	int rowIndex = 0;
	int ColIndex = 0;
	for(int row = 0;row <size;row++)
	{
		for(int col =0;col<size;col++)
		{
			if(row != row1 && col != col1)
			{
				Temp[rowIndex][ColIndex++] = Mat1[row][col];
			}
			if(ColIndex == size-1)
			{
				ColIndex = 0;
				rowIndex++;	
			}
		}
	}
}
void CLinearRegression::MatrixAdjoint(double** Mat1,double **AdjMat)
{
	if((Degree +1) == 1)
	{
		AdjMat[0][0] = 1;
		return;
	}
	int sign = 1;
	double **TempMat = AllocateMemory(Degree+1,Degree+1);
	for(int row =0;row<(Degree+1);row++)
	{
		for(int col = 0;col<(Degree+1);col++)
		{
			MatrixCofactor(Mat1,TempMat,row,col,Degree+1);
			sign = ( (row+col)%2==0)?1:-1;	
			AdjMat[col][row] = (sign)*(MatrixDeterminate(TempMat,Degree));
		}
	}
	
}
void CLinearRegression::MatrixInverse(double** Mat1,double **InverseMat)
{
	double detreminant = MatrixDeterminate(Mat1,Degree+1);  	
	double** AdjMat = AllocateMemory(Degree+1,Degree+1);
	MatrixAdjoint(Mat1,AdjMat);
	for(int row=0;row<Degree+1;row++)
	{
		for(int col=0;col<Degree+1;col++)
		{
			if(0!=detreminant)
			{
				InverseMat[row][col] = AdjMat[row][col]/detreminant;
			}
			else
			{
				InverseMat[row][col] = AdjMat[row][col];
			}
		}
	}
	
}
void CLinearRegression::Display()
{
	for(int row = 0;row<3;row++)
	{
		std::cout<<std::fixed<<std::setprecision(4)<<"w"<<row<<"="<<Weight[row][0]<<std::endl;
	}
}
