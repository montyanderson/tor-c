# tor-c
C library to connect through Tor.

## Example

``` C
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

		buffer[recv_res] = 0x00; // append null character to string
		printf("%s", buffer);
	}
}
```

```
$ ./a.out
HTTP/1.0 302 Found
Cache-Control: private
Content-Type: text/html; charset=UTF-8
Location: http://www.google.de/?gfe_rd=cr&ei=yVpBWKO4C8LG8AeW2oRw
Content-Length: 256
Date: Fri, 02 Dec 2016 11:28:09 GMT

<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>302 Moved</TITLE></HEAD><BODY>
<H1>302 Moved</H1>
The document has moved
<A HREF="http://www.google.de/?gfe_rd=cr&amp;ei=yVpBWKO4C8LG8AeW2oRw">here</A>.
</BODY></HTML>
```
