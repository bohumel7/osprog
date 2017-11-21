#ifndef HAVE_READER_H
#define HAVE_READER_H 1

class Client;

class Reader {
public:
	/**
	 * Creates a new reader.
	 *
	 * @param client a pointer the client this reader is part of.
	 * @param fd the socket to read from.
	 */
	Reader(Client *client, int fd);

	/**
	 * Reads data from #fd and adds it to ringbuffers of all clients.
	 */
	void run();
};

#endif//HAVE_READER_H
