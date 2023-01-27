all: TextWriter
TextWriter: TextWriter.o RandWriter.o test.o
	g++ -g -O3 TextWriter.o RandWriter.o test.o -o TextWriter -lboost_unit_test_framework
TextWriter.o: TextWriter.cpp
	g++ -c TextWriter.cpp
RandWriter.o: RandWriter.h RandWriter.cpp
	g++ -c RandWriter.cpp
test.o: test.cpp
	g++ -c test.cpp
clean:
	rm *.o TextWriter
