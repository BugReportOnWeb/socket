#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "3490"
#define MAX_BUF_SIZE 256

int main(int argc, char **argv) {
    struct addrinfo hints, *res;
    int status, sockfd;
    char buf[MAX_BUF_SIZE];
    size_t len;
    ssize_t bytes_recv;

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
        perror("socket");
        return 1;
    }

    // Conecting to the server
    status = connect(sockfd, res -> ai_addr, res -> ai_addrlen);

    if (status == -1) {
        perror("connect");
        return 1;
    }

    // Receive message from the server
    len = sizeof buf; 
    bytes_recv = recv(sockfd, buf, len - 1, 0);

    if (bytes_recv == -1) {
        perror("recv");
        return 1;
    }

    buf[bytes_recv] = '\0';

    // Printing the message and closing the socket
    printf("Received: %s\n", buf);
    close(sockfd);

    return 0;
}
