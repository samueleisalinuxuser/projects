#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_NICKNAME_LENGHT 9
#define MAX_PASSWORD_LENGHT 20
#define MAX_MESSAGES 2000

int clientFd;

struct hostent *LiberaChatHostName;
struct sockaddr_in LiberaChat;

char nickname[MAX_NICKNAME_LENGHT];
char password[MAX_PASSWORD_LENGHT];

char serverMessages[MAX_MESSAGES], clientMessages[MAX_MESSAGES];

int initializeSocket();
int initializeServers();
int connectToIRCServer(struct sockaddr_in IRCServer);

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("\n[ ERROR / main() ]\n\targv[1] : nickname\n\targv[1] : password\n");

        return -1;
    } else {
        strcpy(nickname, argv[1]);
        strcpy(password, argv[2]);

        printf("\n[ DEBUG / main() / argc, argv ]\n\tnickname : %s\n\tpassword : %s\n", nickname, password);

    }

    if(initializeSocket() == -1) return -1;

    if(initializeServers() == -1) return -1;

    if(connectToIRCServer(/* TESTING */LiberaChat) == -1) return -1;

    while(true) {
        read(clientFd, serverMessages, 255);
        printf("\n > %s\n", serverMessages);
    }

    return 0;
}

int initializeSocket() {
    clientFd = socket(AF_INET, SOCK_STREAM, 0);

    if(clientFd < 0) {
        printf("\n[ ERROR / initializeSocket() / socket ]\n\tFailed to create socket\n");
        
        return -1;
    }

    printf("\n[ DEBUG / initializeSocket() / socket ]\n\tSocket created\n");

    return 0;
}

int initializeServers() {
    // LiberaChat.sin_addr.s_addr = inet_addr("51.89.226.78"); // irc.libera.chat
    if(inet_pton(AF_INET, "51.89.226.78", &LiberaChat.sin_addr) <= 0) {
        printf("\n[ ERROR / initializeServers() / inet_pton ]\n\tInvalid address or address not supported\n");

        return -1;
    }
    LiberaChat.sin_family = AF_INET;
    LiberaChat.sin_port = htons(6697);

    return 0;
}

int connectToIRCServer(struct sockaddr_in IRCServer) {
    printf("\n[ DEBUG / connectToIRCServer() ]\n\tAttempting to connect to:\n\tsin_addr : %s\n\tsin_port : %d\n", inet_ntoa(IRCServer.sin_addr), IRCServer.sin_port);
    
    if(connect(clientFd, (struct sockaddr *)&IRCServer, sizeof(IRCServer)) < 0) {
        printf("\n[ ERROR / connectToIRCServer() ]\n\tUnable to connect\n");
        
        return -1;
    }

    printf("\n[ DEBUG / connectToIRCServer() ]\n\tConnected\n");

    return 0;
}
