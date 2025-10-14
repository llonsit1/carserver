// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 1200
#define MAXLINE 1000

// Driver code
int main()
{
    char buffer[100];
    char *message = "Hello Client";
    int socketFD;
    int len;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;

    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    socketFD = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // bind server address to socket descriptor
    bind(socketFD, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // receive the datagram
    len = sizeof(cliaddr);

    while (1)
    {
        int n = recvfrom(socketFD, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len); // receive message from server
        if (n < -1)
        {
            break;
        }
        buffer[n] = '\0';
        puts(buffer);
    }

    // send the response
    sendto(socketFD, message, MAXLINE, 0,
           (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}
