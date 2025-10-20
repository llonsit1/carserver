#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <stdbool.h>
#include "motor.h"
#include "wheel.h"
#include "movement.h"

typedef enum
{
    FORWARD,
    BACKWARDS,
    RIGHT,
    LEFT
} CAR_CMDS;

#define ARDUINO_DEVICE "/dev/ttyACM0"
#define ARDUINO_SERIAL_CMD_FORWARD "GO_FORWARD"
#define ARDUINO_SERIAL_CMD_BACKWARDS "GO_BACKWARDS"
#define ARDUINO_SERIAL_CMD_RIGHT "GO_RIGHT"
#define ARDUINO_SERIAL_CMD_LEFT "GO_LEFT"

#define SERVER_PORT 10011
#define MAX_BUF_SIZE 500

static char* sCurrentError = NULL;
static bool sIsInfoFatal = false;

/*
 * @brief Server_Info - wrapper for perror
 * @note This function can abort the program..
 */
void Server_Info(const char *format, ...) {
    va_list arglist;

    if (sCurrentError != NULL) {
        fprintf(stderr, "(Specific error name) %s: ",  sCurrentError);
    } 

    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
    fprintf(stderr, "\n");

    if (sIsInfoFatal) {
        fprintf(stderr, "Fatal error exting server..\n");
        exit(EXIT_FAILURE);
    }

    sCurrentError = NULL;
}


void Server_Warning(char *msg)
{
    puts(msg);
}


void Server_HandleActions(char *action)
{
    if (strcmp(action, "FORWARD") == 0)
    {
        Move_Forward();
        //Server_SendDirectionalCmd(FORWARD);
    }
    else if (strcmp(action, "BACKWARDS") == 0)
    {
        Move_Reverse();
        //Server_SendDirectionalCmd(BACKWARDS);
    }
    else if (strcmp(action, "RIGHT") == 0)
    {
        //Server_SendDirectionalCmd(RIGHT);
    }
    else if (strcmp(action, "LEFT") == 0)
    {
        //Server_SendDirectionalCmd(LEFT);
    } else if (strcmp(action, "STOP") == 0) {
        Move_Stop();
    } else if (strcmp(action, "DIAGONAL_RIGHT") == 0) {
        Move_ForwardRight();
    } else if (strcmp(action, "ROTATE") == 0) {
        Move_Rotate();
    }
}

void Server_Setup()
{
    int serverSocket;              /* socket */
    int portno = SERVER_PORT;      /* port to listen on */
    int clientlen;                 /* byte size of client's address */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    struct hostent *hostp;         /* client host info */
    char *buf;                     /* message buf */
    char *hostaddrp;               /* dotted decimal host addr string */
    int optval;                    /* flag value for setsockopt */
    int n;                         /* message byte size */

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket < 0)
    {
        sIsInfoFatal = true;
        Server_Info("ERROR opening socket");
    }

    /*
     * This let us rerun the server immediately after we abort it
     */
    optval = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)portno);

    if (bind(serverSocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        sIsInfoFatal = true;
        Server_Info("ERROR when binding server address!");
    }

    clientlen = sizeof(clientaddr);

    Server_Info("SUCCESS Server initialized!");

    while (true)
    {
        buf = (char *)malloc(MAX_BUF_SIZE);

        if (buf == NULL)
        {
            Server_Info("ERROR Can't allocate memory!!!!");
        }

        n = recvfrom(serverSocket, buf, MAX_BUF_SIZE, 0, (struct sockaddr *)&clientaddr, &clientlen);

        if (n < 0)
        {
            Server_Info("ERROR Invalid size!");
        }

        printf("Received msg from client: %s\n", buf);

        // Determine who sent the datagram
        hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
				      sizeof(clientaddr.sin_addr.s_addr),
				      AF_INET);

        if (hostp == NULL)
        {
            perror("gethostbyaddr");
            Server_Info("Couldn't determine who sent the package (error code: %d)\n", h_errno);
        }

        hostaddrp = inet_ntoa(clientaddr.sin_addr);
        if (hostaddrp == NULL)
        {
            perror("inet_ntoa");
            Server_Info("ERROR on inet_ntoa\n");
        }

        printf("From client with ip: %s\n", hostaddrp);

        Server_HandleActions(buf);

        free(buf);
    }
}

void Server_Init()
{
    Motor_SetupRPIPins();
    Wheel_Init();
    Server_Setup();
}

int main()
{
    Server_Init();
}
