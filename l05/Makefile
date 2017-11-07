CFLAGS = -Wall -Werror -g
CXXFLAGS = -Wall -Werror -std=c++11 -g

hello_objects := hello.o
echo_objects := echo.o

.PHONY: default all
default: echo
all: hello echo


$(hello_objects) : Makefile
hello: $(hello_objects)

$(echo_objects) : Makefile
echo: $(echo_objects)


.PHONY: clean distclean
clean:
	rm -f *.o
distclean: clean
	rm -f hello echo
