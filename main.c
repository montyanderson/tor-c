#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

union Port {
	uint16_t number;
	char binary[2];
};

#define BUFFER_SIZE 1000000

int main() {
	int sock;
	size_t i;
	size_t j;
	union Port port;
	char remote_host[] = "google.com";
	struct sockaddr_in server;
	char *request, *response;
	char socks_res[8];
	size_t socks_res_i = 0, response_i;
	ssize_t recv_status;

	request = calloc(BUFFER_SIZE, 1);
	response = calloc(BUFFER_SIZE, 1);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0) {
		printf("Failed to create socket!\n");
	}

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(9050);

	if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Failed to connect.\n");
	}

	i = 0;

	port.number = htons(80);

	request[i++] = 0x04; // socks version number
	request[i++] = 0x01; // connect to port
	request[i++] = port.binary[0]; // remote port
	request[i++] = port.binary[1];
	request[i++] = 0x00; // wrong IP address
	request[i++] = 0x00;
	request[i++] = 0x00;
	request[i++] = 0x01;
	request[i++] = 'a'; // user id
	request[i++] = 0x00;

	for(j = 0; remote_host[j]; j++) {
		request[i++] = remote_host[j];
	}

	request[i++] = 0x00;

	if(send(sock, request, i, 0) < 0) {
		printf("Failed to send request to SOCKS server.\n");
	}

	while(socks_res_i < 8) {
		recv_status = recv(sock, response, BUFFER_SIZE, 0);

		if(recv_status < 0) {
			printf("Failed to recv!\n");
		}

		for(i = 0; i < recv_status; i++) {
			socks_res[socks_res_i++] = response[i];
		}
	}

	if(socks_res[1] != 0x5A) {
		printf("Socks failed to connect!\n");
	}

	strcpy(request, "GET http://google.com/\n\n");
	send(sock, request, strlen(request), 0);

	while(1) {
		recv_status = recv(sock, response, BUFFER_SIZE, 0);

		if(recv_status < 1) {
			break;
		}

		response[recv_status + 1] = 0x00;
		printf("%s", response);
	}
}
