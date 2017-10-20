CC = g++
#CFLAG = -g -Wall
CFLAG = -g 

default: naive_bayes

naive_bayes: CFileReading.o CGaussian.o CHistogram.o CMixture.o Main.o
	$(CC) $(CFLAG) -o naive_bayes CFileReading.o CGaussian.o CHistogram.o CMixture.o Main.o

CFileReading.o: CFileReading.cpp CFileReading.h
	$(CC) $(CFLAG) -c CFileReading.cpp

CGaussian.o: CGaussian.cpp CGaussian.h
	$(CC) $(CFLAG) -c CGaussian.cpp

CHistogram.o: CHistogram.cpp CHistogram.h
	$(CC) $(CFLAG) -c CHistogram.cpp

CMixture.o: CMixture.cpp CMixture.h
	$(CC) $(CFLAG) -c CMixture.cpp

Main.o: Main.cpp
	$(CC) $(CFLAG) -c Main.cpp

clean:
	$(RM) naive_bayes *.o
