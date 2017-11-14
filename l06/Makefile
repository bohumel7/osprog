CXXFLAGS = -std=c++11 -Wall -I../test
LINK.o = $(LINK.cc) # we're linking c++ objects

runTest: test
	./test

test: test.o TestRingBuffer.o RingBuffer.o TestWriter.o Writer.o
