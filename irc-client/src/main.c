#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define EXPECTED_ARGV 5
#define MAX_NICKNAME_LENGHT 9
#define MAX_PASSWORD_LENGHT 20
#define SERVER_HOSTNAME_LENGHT 20
#define BUFFER_LENGHT 2000

char nickname[MAX_NICKNAME_LENGHT];
char password[MAX_PASSWORD_LENGHT];
char serverHostName[SERVER_HOSTNAME_LENGHT];
int serverPort;

int createNewSocket();
struct sockaddr_in createNewServerAddress(char *hostname, int port);

// test
void test();
// end test

int main(int argc, char *argv[]) {
    if(argc < EXPECTED_ARGV) return 1;

    strcpy(nickname, argv[1]);
    strcpy(password, argv[2]);
    strcpy(serverHostName, argv[3]);
    serverPort = atoi(argv[4]);

    // test
    test();
    // end test

    return 0;
}

int createNewSocket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in createNewServerAddress(char *hostname, int port) {
    struct hostent *he;
    struct sockaddr_in newServerAddress;

    he = gethostbyname(hostname);

    newServerAddress.sin_family = AF_INET;
    newServerAddress.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)he -> h_addr));
    newServerAddress.sin_port = htons(port);

    return newServerAddress;
}

// test
void test() {
    int newTestSocketFileDescriptor = createNewSocket();
    struct sockaddr_in newTestServerAddress = createNewServerAddress(serverHostName, serverPort);
    int newTestConnection = connect(newTestSocketFileDescriptor, (struct sockaddr_in *)&newTestServerAddress, sizeof(newTestServerAddress));
    printf("\nconnection = %d\n", newTestConnection);

    char newTestBuffer[BUFFER_LENGHT];

    while(true) {
        int readBlock = read(newTestSocketFileDescriptor, newTestBuffer, sizeof(newTestBuffer));
        printf("%s\n", newTestBuffer);

        bzero(newTestBuffer, sizeof(newTestBuffer));
    }
}
// end test
