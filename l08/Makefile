CXXFLAGS = -std=c++11 -Wall -pthread
CFLAGS = -Wall -pthread
LDFLAGS = -pthread
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH) # we're linking c++ objects

shell: shell.o

clean:
	rm -f *.o
distclean: clean
	rm -f shell

.PHONY: clean distclean
