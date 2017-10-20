#ifndef FILEREADING_H
#define FILEREADING_H

#include<string>
#include<vector>
#include<map>
#include<cstring>
#include<fstream>
#include"Utility.h"


class CFileReading
{
	public:
		eErrorType OpenFile(std::string FileName);
		eErrorType CloseFile();
		eErrorType GetLine(std::string& Line);
	private:
		
		std::string FileName;
		std::ifstream FileStream;
};

#endif
