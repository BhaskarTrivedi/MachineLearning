How to Compile and execute file

Step 


1) Navigate to decision_trees directory


2) Tpye "make"

3) press "Enter"
, it will create executable and required object file
	
	
	As example 
	
		
	[bct8665@omega linear_regression]$ make
		
	g++ -g  -c CFileReading.cpp
	g++ -g  -c CDecisionTree.cpp
	CDecisionTree.cpp: In member function ‚TreeNode* CDecisionTree::DecisionTreeLearning(double**, int, int)‚:
	CDecisionTree.cpp:347: warning: converting to ‚int‚ from ‚double‚
	g++ -g  -c Main.cpp
	g++ -g  -o dtree CFileReading.o CDecisionTree.o Main.o

4) Type "./dtree pendigits_training.txt pendigits_test.txt optimized 50" and Press Enter to run to execute Optimized Decision tree		
	
	As Example : 
	[bct8665@omega naive_bayes]$ ./dtree pendigits_training.txt pendigits_test.txt optimized 50
