CC = g++
#CFLAG = -g -Wall
CFLAG = -g 

default: dtree 

dtree: CFileReading.o  CDecisionTree.o Main.o
	$(CC) $(CFLAG) -o dtree CFileReading.o CDecisionTree.o Main.o

CFileReading.o: CFileReading.cpp CFileReading.h
	$(CC) $(CFLAG) -c CFileReading.cpp

CDecisionTree.o: CDecisionTree.cpp CDecisionTree.h
	$(CC) $(CFLAG) -c CDecisionTree.cpp

Main.o: Main.cpp
	$(CC) $(CFLAG) -c Main.cpp

clean:
	$(RM) dtree *.o
