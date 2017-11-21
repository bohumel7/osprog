#ifndef HAVE_CLIENT_H
#define HAVE_CLIENT_H 1

class Server;

class Client {
public:
	/**
	 * Creates a new client.
	 *
	 * @param server  a pointer the server, used to access the list
	 * of other clients.
	 * @param fd the socket to read from.
	 */
	Client(Server *server, int fd);

	/**
	 * Returns a pointer to the server
	 * (i.e. to access the client list).
	 */
	Server* server();

	/**
	 * Starts the reader and writer threads for this client.
	 */
	void start();
};

#endif//HAVE_CLIENT_H
