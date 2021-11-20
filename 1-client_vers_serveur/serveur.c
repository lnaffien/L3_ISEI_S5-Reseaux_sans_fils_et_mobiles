#include "./commun.h"

int main()
{
	char buffer[1024];
	int socket_server = socket(AF_INET, SOCK_STREAM, 0);
	printf("Initialisation des sockets : OK\n");

	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(socket_server, (struct sockaddr *) &server_addr, sizeof(server_addr));
	printf("Bind du socket : OK\n");
	listen(socket_server, 5);
	printf("Etat du serveur : ECOUTE\n");
	int new_socket_server = accept(socket_server, (struct sockaddr *) &server_addr, sizeof(server_addr));
	printf("Communication validee : demarrage du transferts de donnees\n");

	//lecture des donnees
	read(new_socket_server, buffer, 1024);
	printf("Reception du message : OK\n");
	printf("Message recu : %s\n", buffer);

	bzero(buffer, 1024); //reinitialisation du buffer

	close(new_socket_server);

	return 0;
}