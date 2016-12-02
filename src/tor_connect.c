#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "tor_connect.h"

int tor_connect(int tor_port, char *remote_host, int remote_port) {
	int sock;
	struct sockaddr_in server_addr;
	char socks_res[8];

	tor_port = htons(tor_port);
	remote_port = htons(remote_port);

	char socks_headers[] = {
		0x04,
		0x01,
		((char *) &remote_port)[0],
		((char *) &remote_port)[1],
		0x00,
		0x00,
		0x00,
		0x01,
		'a',
		0x00
	};

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0) return -1;

	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = tor_port;

	if(connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) return -1;
	if(send(sock, socks_headers, sizeof(socks_headers), 0) < 0) return -1;
	if(send(sock, remote_host, strlen(remote_host) + 1, 0) < 0) return -1;
	if(recv(sock, &socks_res, sizeof(socks_res), 0) < 0) return -1;
	if(socks_res[1] != 0x5A) return -1;

	return sock;
}
