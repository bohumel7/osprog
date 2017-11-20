CXXFLAGS = -std=c++11 -Wall -I../test -pthread
LDFLAGS = -pthread
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH) # we're linking c++ objects

runTest: test
	./test

test: test.o TestRingBuffer.o RingBuffer.o TestWriter.o Writer.o

clean:
	rm -f *.o
distclean: clean
	rm test

.PHONY: runTest clean distclean
