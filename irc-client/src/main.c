#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_MESSAGES 2000

int socketDescriptor;
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

    quit();

    return 0;
}

void initializeServers() {
    LiberaChat.sin_family = AF_INET;
    LiberaChat.sin_addr.s_addr = inet_addr(getaddrinfo("irc.libera.chat"));
    LiberaChat.sin_port = htons(6697);
}

int initializeSocket() {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(socketDescriptor < 0) {
        printf("[ ERROR ] initialize() socketDescriptor Failed to create socket\n");

        return -1;
    }

    printf("[ LOG ] initialize() socketDescriptor Socket created\n");

    return 0;
}

int connectToIRCServer(struct sockaddr_in IRCServer) {
    if(connect(socketDescriptor, (struct sockaddr *)&IRCServer, sizeof(IRCServer)) < 0) {
        printf("[ ERROR ] connectToIRCServer Unable to connect to %s : %d\n", IRCServer.sin_addr, IRCServer.sin_port);

        return -1;
    }

    printf("[ LOG ] connectToIRCServer() Connected %s : %d\n", IRCServer.sin_addr, IRCServer.sin_port);

    return 0;
}

void quit() {
    quit(socketDescriptor);
}
