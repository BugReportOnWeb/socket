#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "3490"
#define BACKLOG 10
#define MAX_LEN 256

int main(int argc, char **argv) {
    struct addrinfo hints, *res;
    int status, sockfd, new_fd;

    struct sockaddr_storage cli_addr;
    socklen_t addr_size;

    char msg[MAX_LEN];
    char buf[MAX_LEN];
    size_t len;
    ssize_t bytes_send, bytes_recv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;          // IPv4
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags = AI_PASSIVE;        // Use my IP

    // Setting up info for addrinfo on res (linked list)
    status = getaddrinfo(NULL, PORT, &hints, &res);

    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    // Creating a socket file descriptor
    sockfd = socket(res -> ai_family, res -> ai_socktype, res -> ai_protocol);

    if (sockfd == -1) {
        perror("sockfd");
        return 1;
    }

    // Binding socket to PORT on localhost
    status = bind(sockfd, res -> ai_addr, res -> ai_addrlen);

    if (status == -1) {
        perror("bind");
        return 1;
    }

    // Listening for incoming connection requests
    status = listen(sockfd, BACKLOG);

    if (status == -1) {
        perror("listen");
        return 1;
    }

    // Accepting a connection from client
    addr_size = sizeof cli_addr;
    new_fd = accept(sockfd, (struct sockaddr *) &cli_addr, &addr_size);

    if (new_fd == -1) {
        perror("accept");
        return 1;
    }

    while (1) {
        // Receiving message from the client
        bzero(buf, sizeof buf);
        len = sizeof buf; 
        bytes_recv = recv(new_fd, buf, len - 1, 0);

        if (bytes_recv == -1) {
            perror("recv");
            return 1;
        }

        // Printing and clearing buffer
        buf[bytes_recv] = '\0';
        printf("Client: %s\n", buf);

        status = strncmp("Bye", buf, 3);
        if (status == 0) break;

        bzero(buf, sizeof buf);

        // Sending message to the client
        printf("You: ");
        scanf("%[^\n]%*c", msg);

        len = strlen(msg);
        bytes_send = send(new_fd, msg, len, 0);

        if (bytes_send == -1) {
            perror("send");
            return 1;
        }

        status = strncmp("Bye", msg, 3);
        if (status == 0) break;
    }

    // Cleaning up by closing the socket
    close(new_fd);

    return 0;
}
