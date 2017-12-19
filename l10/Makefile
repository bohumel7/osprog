CXXFLAGS = -std=c++11 -Wall
CFLAGS = -Wall
LDFLAGS = -pthread
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH) # we're linking c++ objects

procs: procs.o

clean:
	rm -f *.o
distclean: clean
	rm -f procs

.PHONY: clean distclean

