#include"CFileReading.h"
#include<stdlib.h>
#include<iostream>
#include<algorithm>


eErrorType CFileReading::OpenFile(std::string FileName)
{
	eErrorType Error = SUCCESS;
	this->FileName = FileName;
	FileStream.open(this->FileName.c_str());
	if(!(FileStream.is_open()))
	{
		std::cout<<"File Error : "<<FileName<<std::endl;
		Error = FILEOPENFAIL;
	}
	return Error;
}

eErrorType CFileReading::CloseFile()
{
	eErrorType Error = SUCCESS;
	FileStream.close();
	return Error;
}
eErrorType CFileReading::GetLine(std::string& LineData)
{
	eErrorType Error = SUCCESS;
	std::string Line;
	if(this->FileStream.is_open())
	{
		if(getline(this->FileStream, Line))
		{
			LineData = Line;
		}	
		else
		{
			Error = ENDOFFILE;
		}
	}
	else
	{
		Error = FAIL;
	}
	return Error;
}
