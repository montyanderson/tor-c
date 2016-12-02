#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "tor_connect.h"

int main() {
	int sock;
	ssize_t i, recv_res;
	char request[] = "GET http://google.com/\n\n";
	char buffer[500];

	sock = tor_connect(9050, "google.com", 80);

	if(sock < 0) {
		printf("Failed to connect to socket!\n");
		return 1;
	}

	if(send(sock, request, strlen(request), 0) < 0) {
		printf("Failed to send!\n");
		return 1;
	}

	while(1) {
		recv_res = recv(sock, &buffer, sizeof(buffer), 0);

		if(recv_res < 0) {
			break;
		}

		buffer[recv_res] = 0x00; /* append null character to string */
		printf("%s", buffer);
	}
}
