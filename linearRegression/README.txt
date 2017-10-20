How to Compile and execute file

Step 

1) Navigate to linear_regression directory

2) Tpye "make"
3) press "Enter"
, it will create executable and required object file
	
	As example 
	
		[bct8665@omega linear_regression]$ make
		g++ -g  -c CFileReading.cpp
		g++ -g  -c CLinearRegression.cpp
		g++ -g  -c Main.cpp
		g++ -g  -o linear_regression CFileReading.o CLinearRegression.o Main.o
4) Type "./linear_regression sample_data1.txt 1 0" and Press Enter to run to execute one degree polynomial and lamda 0
		
	As Example : [bct8665@omega naive_bayes]$ ./linear_regression sample_data1.txt 1 0 
