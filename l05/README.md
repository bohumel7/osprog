Lab 5
=====

Submit the solution to [Echor](#echo) tasks
according to the [Submitting instructions](#submitting) before Tuesday Nov 14
23:59:59.



Hello
-----

Write a "hello" TCP server. It will listen for TCP connections on a port given
as its first argument (on any address). For every connection, it will read a
"name" from the client (up to first newline, max 60 bytes) and then send
back the string "Hello `<name>`!\n" (where `<name>` is the name read from client
and `\n` is a newline character).

Example:

```sh
./hello 12345
```

```sh
nc localhost 12345
YoYo
Hello YoYo!
Alexander the Great
Hello Alexander the Great!
```

Note: one "uncooperative" client should not be able to disruption the
functionality for others, i.e. this client should not stop others from getting
responses:

```sh
(echo -n first; sleep 1000; echo last) | nc -q0 localhost 12345
```

There are two basic ways how to solve this: either using threads or asynchronous
(non-blocking) IO. Threaded code is usually easier to write if the threads don't
interact much  (such as in this case), but can become complex / inefficient if a
lot of synchronization is needed. Asynchronous code is usually a bit harder to
write upfront (though this depends on available libraries / frameworks)

### Threads

Everytime you `accept` a connection, just start a new thread (functione) that
handles the connection. You should `join` threads when they are finished.

Creating new threads and destroying them are *slightly* expensive operations,
so for performance reasons *thread pools* are used sometimes: when a thread
finishes its task, it isn't destroyed but added to a list of *available* threads
that can be reused for other operations. The code to manage all this however
becomes more complicated (the main thread function must add the thread to a
central list and also check some sort of an inbox (queue) for new task, both of
which need synchronization).

For the program to be always responsive to new connections, we still need new
threads for all simultaneous connections, which can result in a large ammounts
of threads (imagine thousands of mobile applications connecting to a server to
receive events that don't happen very often).

### Asynchronous

There are two basic problems to solve when handling asynchronous IO:
handling the asynchronous operations themselves (i.e. `select`/`poll`)
and managing the state of the various "task" that we are "juggling" at the same
time.

With threads, all the context (data, state, ...) for one "task" (i.e. handling
one connection) could be stored locally in a function. In an asynchronous
framework we need to pause and resume the tasks depending on the state of the
async operations.

In our case this mean that we need to remember a buffer and the size of data it
stores for each connection.

Echo
------

Implement an echo server, i.e. a server that "echoes" (sends back) everything
the client sends. Implement a program that will listen for TCP connection on a
port give as its first argument (on any address).

Your server should behave correctly even if a client is reading more slowly
then sending data (the server should stop reading data from him until it can
again send more data).

Submitting
----------

Submit your solution by committing required files (at least `echo.cpp`)
under the directory `l05` and creating a pull request against the `l05` branch.

If you split your solution into multiple files, modify appropriately the
dependencies of the `echo` target in the Makefile

A correctly created pull request should appear in the
[list of PRs for `l05`](https://github.com/pulls?utf8=%E2%9C%93&q=is%3Aopen+is%3Apr+user%3AFMFI-UK-2-AIN-118+base%3Al05).
