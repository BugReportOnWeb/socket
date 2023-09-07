# Socket

A simple networking application in C that demonstrates how to create a client that connects to a server, sends and receives data over a TCP/IP connection.

## Prerequisites

Before running the application, ensure you have the following prerequisites:

- C compiler (e.g., GCC)
- A Unix-like operating system (Linux, macOS, etc.)

## Usage

1. Clone the repository to your local machine:

```bash
git clone https://github.com/BugReportOnWeb/socket.git
cd socket
```

2. Compile the client and server programs:

```bash
gcc -o server server.c
gcc -o client client.c
```

3. Startart the server:

```bash
./server
```

The server will start listening on a specified port.

4. Run the client:

```bash
./client
```

The client will connect to the server and display the received message from the server.

## Code Overview

- `server.c`: Contains the code for the server-side of the example. It listens for incoming connections and handles client requests.
- `client.c`: Contains the code for the client-side of the example. It connects to the server and communicates by sending or receiving messages.

## Customization

- You can modify the code to implement your own networking protocols or application logic.
- Adjust the port number and IP address in the code to match your network configuration.
