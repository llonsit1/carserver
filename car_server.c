#include "global.h"
#include "motor.h"
#include "wheel.h"
#include "movement.h"
#include "hash.h"
#include "servo.h"

typedef enum
{
    FORWARD,
    BACKWARDS,
    RIGHT,
    LEFT
} CAR_CMDS;

#define SERVER_PORT 10011
#define MAX_BUF_SIZE 500

#define HASH_FORWARD 4
#define HASH_LEFT 97
#define HASH_RIGHT 40
#define HASH_REVERSE 10
#define HASH_RIGHT_DIAGONAL 91
#define HASH_LEFT_DIAGONAL 26
#define HASH_REVERSE_LEFT 76
#define HASH_REVERSE_RIGHT 82
#define HASH_ROTATE 65
#define HASH_SERVO_UP 84
#define HASH_SERVO_DOWN 99
#define HASH_SERVO_STOP 66
#define HASH_STOP 16

static char* sCurrentError = NULL;
static bool sIsInfoFatal = false;

/*
 * @brief Server_Info - wrapper for perror
 * @note This function can abort the program..
 */
static void Server_Info(const char *format, ...) {
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

static void Server_Warning(char *msg)
{
    puts(msg);
}

static void Server_HandleCarAction(char *action)
{
    int code = hash(action);

    switch (code) {
        case HASH_FORWARD:
            Move_Forward();
            break;
        case HASH_REVERSE:
            Move_Reverse();
            break;
        case HASH_LEFT:
            Move_Left();
            break;
        case HASH_RIGHT:
            Move_Right();
            break;
        case HASH_RIGHT_DIAGONAL:
            Move_ForwardRight();
            break;
        case HASH_LEFT_DIAGONAL:
            Move_ForwardLeft();
            break;
        case HASH_REVERSE_LEFT:
            Move_ReverseLeft();
            break;
        case HASH_REVERSE_RIGHT:
            Move_ReverseRight();
            break;
        case HASH_ROTATE:
            Move_Rotate();
            break;
        case HASH_SERVO_UP:
            Move_ServoUp();
            break;
        case HASH_SERVO_DOWN:
            Move_ServoDown();
            break;
        case HASH_SERVO_STOP:
            Move_ServoStop();
            break;
        case HASH_STOP:
            Move_Stop();
            break;
        default:
            Server_Info("Invalid command!\n ");
            break;
    }
}

static void Server_Setup()
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

        Server_HandleCarAction(buf);

        free(buf);
    }
}

static void Server_Init()
{
    Motor_SetupRPIPins();
    Servo_Init();
    Wheel_Init();
    Server_Setup();
}

int main()
{
    Server_Init();
}
