Lab 6
=====

Submit the solution to both tasks according to the
[Submitting instructions](#submitting) before Tuesday
Nov 14 23:59:59.

*These tasks are "preparation" for a threaded "TCP chat" server
that we will implement in the next assignemt.*


RingBuffer
----------

Implement a [ring buffer](https://en.wikipedia.org/wiki/Circular_buffer)
(also known as a circular buffer) as `RingBuffer` class.
It should support all the operations defined in the
[`RingBuffer.h`](RingBuffer.h) header.

Writer
------

Implement a "writer" that can be used to write all the data coming into a
ring buffer into a file descriptor. See the requirements in the
[`Writer.h`](Writer.h) header.

Submitting
----------

Submit your solution by modifying committing required files
under the directory `l06` and creating a pull request against the `l06` branch.

If you split your solution into multiple files, modify appropriately the
dependencies of the `echo` target in the Makefile

A correctly created pull request should appear in the
[list of PRs for `l06`](https://github.com/pulls?utf8=%E2%9C%93&q=is%3Aopen+is%3Apr+user%3AFMFI-UK-2-AIN-118+base%3Al06).
