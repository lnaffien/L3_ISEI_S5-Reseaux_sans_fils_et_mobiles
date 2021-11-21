#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define PORT 4440
#define BUFFER_TAILLE 1024

void init_server_addr(struct sockaddr_in * server_addr)
{
	memset(server_addr, '\0', sizeof(server_addr));
	(*server_addr).sin_family = AF_INET;
	(*server_addr).sin_port = htons(PORT);
	(*server_addr).sin_addr.s_addr = inet_addr("127.0.0.1");
}
