#include"CLinearRegression.h"
#include"Utility.h"
#include<string>
#include<iostream>
#include<stdlib.h>

void LinearRegression(std::string FileName,std::string Degree,std::string strLamda);

int main(int argc,char* argv[])
{
	std::string strLamda = "";
	if(argc < 3)
        {
                std::cout<<"Too few parameter!! "<<std::endl;
                return 0;
        }
	if(argc >= 4)
	{
		strLamda = argv[3];
	}
	LinearRegression(argv[1],argv[2],strLamda);
	

	return 0;
}
void LinearRegression(std::string FileName,std::string Degree,std::string strLamda)
{
	
	CLinearRegression LinearObj;
	int degree = 0;
	degree = atoi(Degree.c_str());
	double Lamda = 0;
	if(strLamda.length() !=0)
	{
		Lamda = atof(strLamda.c_str());
	}
	LinearObj.FileReading(FileName);
	LinearObj.LinearRegression(degree,Lamda);
	LinearObj.Display();
}
