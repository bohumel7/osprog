#include "catch.hpp"

#include "Writer.h"
#include "RingBuffer.h"
#include <unistd.h>

int pipefd[2];

SCENARIO("Writer", "[writer]") {
	const char textBuf[] = "abcdefghijklmnopqrstuvwxyzABCDEF";
	if (pipe2(pipefd, 0) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	GIVEN("A Writer over a pipe") {
		Writer w(pipefd[1], 16);

		THEN("Data can be added to the ring buffer") {
			REQUIRE(w.add(textBuf, 32) == 16);
		}
	}
}

/* vim: set sw=4 sts=4 ts=4 noet : */
