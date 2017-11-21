CXXFLAGS = -std=c++11 -Wall -I../test -pthread
LDFLAGS = -pthread
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH) # we're linking c++ objects

chat: chat.o Server.o Client.o Reader.o Writer.o RingBuffer.o

clean:
	rm -f *.o
distclean: clean
	rm chat

.PHONY: clean distclean
