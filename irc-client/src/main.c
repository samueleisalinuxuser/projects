#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define EXPECTED_ARGC 4
#define MAX_NICKNAME_LENGHT 9
#define MAX_PASSWORD_LENGHT 20

char nickname[MAX_NICKNAME_LENGHT], password[MAX_PASSWORD_LENGHT], rawIRCServers[500];

/* NOTE
 * rawIRCServers should be inserted like: irc.server0.sever0:port,irc.server1.server1:port
 */

int resolveDNS();

int main(int argc, char *argv[]) {
    if(argc < EXPECTED_ARGC) {
        printf("invalid arguments\n");

        return 1;
    } else {
        strcpy(nickname, argv[1]);
        strcpy(password, argv[2]);
        strcpy(rawIRCServers, argv[3]);

        printf("debug:\n\tnickname: %s\n\tpassword: %s\n", nickname, password);
    }

    return 0;
}

int resolveDNS() {
}
