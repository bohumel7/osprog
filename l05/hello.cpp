#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_ntoa

void err(const char *msg) { perror(msg); exit(EXIT_FAILURE); }

/**
 * Reads a line (terminated by \n) from fd,
 * but only up to maxSize bytes.
 *
 * @returns number of bytes read (incl. \n if it was present
 * in first maxSize bytes).
 *
 * Note: there is now way to find out how much data was actually read
 * before an error occured.
 */
ssize_t readLine(int fd, char *buffer, size_t maxSize) {
	size_t bytesRead = 0;
	while(bytesRead < maxSize) {
		ssize_t count = read(fd, buffer, maxSize - bytesRead);
		if (count == -1) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		if (count == 0)
			return bytesRead; // EOF
		for (int i = 0; i < count; ++i) {
			if (buffer[bytesRead + i] == '\n')
				return bytesRead + i;
		}
	}
	return bytesRead;
}

/**
 * Writes until all the data are written or an arror
 * is encountered.
 *
 * @returns either size or -1
 *
 * Note: there is now way to find out how much data was actually written
 * before an error occured.
 */
ssize_t writeAll(int fd, const char *buffer, size_t size) {
	size_t bytesWritten = 0;
	while (bytesWritten < size) {
		ssize_t count = write(fd, buffer + bytesWritten, size - bytesWritten);
		if (count == -1) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		bytesWritten += count;
	}
	return bytesWritten;
}

/*
 * basically equivalent to this python:
 *     line = sock.readLine(60).
 *     sock.write('Hello ' + line.rstrip('\n') + '!\n')
 */
void greetClient(int sock)
{

	char buffer[70] = "Hello ";  // Need space for "Hello " + max 60 bytes + "!\n"

	size_t pos = strlen(buffer);
	ssize_t lineSize = readLine(sock, buffer + pos, sizeof(buffer) - pos);
	if (lineSize == -1) {
		perror("Error reading from client");
		close(sock);
		return;
	}

	pos += lineSize;
	buffer[pos++] = '!';
	buffer[pos++] = '\n';

	size_t bytesWritten = 0;
	while (bytesWritten < pos) {
		ssize_t count = write(sock, buffer + bytesWritten, pos - bytesWritten);
		if (count == -1) {
			if (errno == EINTR)
				continue;
			else {
				perror("Error writing to client");
				close(sock);
				return;
			}
		}
		bytesWritten += count;
	}
	close(sock);
}

int main(int argc, char* argv[])
{
	int serverSock;

	if (argc < 2) {
		fprintf(stderr, "USAGE:\n");
		fprintf(stderr, "  hello PORT_NUMBER\n");
		exit(EXIT_FAILURE);
	}

	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock == -1)
		err("socket");

	uint16_t portno = atoi(argv[1]);  // TODO strtol to detect errors

	struct sockaddr_in addr; // ipv4 address and port
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY; // listen on any address / interface
	addr.sin_port = htons(portno); // convert port number to network byte order

	if (bind(serverSock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		err("bind");

	if (listen(serverSock, 10) == -1)
		err("listen");

	while (1) {
		struct sockaddr_in clientAddr;
		socklen_t clientAddrSize = sizeof(clientAddr);
		// wait for new connctions
		int clientSock = accept(serverSock, (struct sockaddr *) &clientAddr,
				&clientAddrSize);
		if (clientSock == -1 && (errno != EAGAIN || errno != EINTR))
			err("accept");

		if (clientSock != -1) {
			// we have a new connection
			fprintf(stderr, "New connection from %s:%d\n",
					inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

			// TODO asynchronously!
			greetClient(clientSock);
		}
	}
}

/* vim: set sw=4 sts=4 ts=4 noet : */
