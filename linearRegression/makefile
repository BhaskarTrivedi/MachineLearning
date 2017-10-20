CC = g++
#CFLAG = -g -Wall
CFLAG = -g 

default: linear_regression 

linear_regression: CFileReading.o CLinearRegression.o Main.o
	$(CC) $(CFLAG) -o linear_regression CFileReading.o CLinearRegression.o Main.o

CFileReading.o: CFileReading.cpp CFileReading.h
	$(CC) $(CFLAG) -c CFileReading.cpp

CLinearRegression.o: CLinearRegression.cpp CLinearRegression.h 
	$(CC) $(CFLAG) -c CLinearRegression.cpp

Main.o: Main.cpp
	$(CC) $(CFLAG) -c Main.cpp

clean:
	$(RM) linear_regression *.o
