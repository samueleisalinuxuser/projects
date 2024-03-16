#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define LIBERA_CHAT_ADDRESS "51.89.226.78" // "irc.libera.chat"
#define LIBERA_CHAT_PORT 6697
/* [ useless binding ] */ #define ADDRESS LIBERA_CHAT_ADDRESS // remove
/* [ useless binding ] */ #define PORT LIBERA_CHAT_PORT // remove
#define MAX_MESSAGES 2000
#define NICKNAME_MAX_LENGHT 9

int socketDescriptor;
struct sockaddr_in serverAddress;
char serverMessages[MAX_MESSAGES], clientMessages[MAX_MESSAGES];

int initialize();

int main() {
    initialize();

    return 0;
}

int initialize() {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); // socket(int domain, int type, int protocol);

    if(socketDescriptor < 0) {
        printf("[ ERROR ] initialize() socketDesciptor Unable to connect\n");
        
        return -1;
    }

    printf("[ LOG ] initialize() socketDescriptor Socket created\n");

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(ADDRESS);

    if(connect(socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("[ ERROR ] initialize() connect() Unable to connect\n");

        return -1;
    }

    /* fix preprocessor here */ printf("[ LOG ] initialize() connect() Connected to %s : %s\n", ADDRESS, PORT);

    return 0;
}
