#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_MESSAGES 2000

int socketDescriptor;
struct hostent *LiberaChatHostName;
struct sockaddr_in LiberaChat;
char serverMessages[MAX_MESSAGES], clientMessages[MAX_MESSAGES];

void initializeServers();
int initializeSocket();
int connectToIRCServer(struct sockaddr_in IRCServer);
void quit();

int main() {
    initializeServers();

    initializeSocket();

    /* [ TESTING ] */ connectToIRCServer(LiberaChat);
    
    return 0;
}

void initializeServers() {
    LiberaChatHostName = gethostbyname("irc.libera.chat");
    LiberaChat.sin_family = AF_INET;
    if(inet_pton(AF_INET, LiberaChatHostName -> h_addr, &LiberaChat.sin_addr) <= 0) printf("\n[ ERROR ] [ initializeServers() ] [ LiberaChat / LiberaChatHostName ]\n\tAddress not supported\n");
    // LiberaChat.sin_addr.s_addr = inet_addr(LiberaChatHostName -> h_addr);
    LiberaChat.sin_port = htons(6697);
}

int initializeSocket() {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(socketDescriptor < 0) {
        printf("\n[ ERROR ] [ initialize() ] [ socketDescriptor ]\n\tFailed to create socket\n");

        return -1;
    }

    printf("\n[ LOG ] [ initialize() ] [ socketDescriptor ]\n\tSocket created\n");

    return 0;
}

int connectToIRCServer(struct sockaddr_in IRCServer) {
    if(connect(socketDescriptor, (struct sockaddr *)&IRCServer, sizeof(IRCServer)) < 0) {
        printf(
            "\n[ ERROR ] [ connectToIRCServer ]\
            \n\tUnable to connect to:\
            \n\t[ IRCServer.sin_addr ] : %s\
            \n\t[ <chat>HostName -> h_addr ] : %s\
            \n\t[ <chat>HostName -> h_name ] : %s\
            \n\t[ IRCServer.sin_port ] : %d\
            \n",
            (char *)inet_ntoa(IRCServer.sin_addr),
            inet_ntoa(*(struct in_addr *)LiberaChatHostName -> h_addr),
            LiberaChatHostName -> h_name,
            IRCServer.sin_port
        );

        return -1;
    }

    printf(
        "\n[ ERROR ] [ connectToIRCServer ]\
        \n\tConnect to:\
        \n\t[ IRCServer.sin_addr ] : %s\
        \n\t[ <chat>HostName -> h_addr ] : %s\
        \n\t[ <chat>HostName -> h_name ] : %s\
        \n\t[ IRCServer.sin_port ] : %d\
        \n",
        (char *)inet_ntoa(IRCServer.sin_addr),
        inet_ntoa(*(struct in_addr *)LiberaChatHostName -> h_addr),
        LiberaChatHostName -> h_name,
        IRCServer.sin_port
    );

    return 0;
}
