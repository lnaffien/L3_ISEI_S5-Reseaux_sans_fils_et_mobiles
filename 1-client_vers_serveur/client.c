#include "./commun.h"

int main()
{
	char buffer[1024];
	int socket_client = socket(AF_INET, SOCK_STREAM, 0);
	printf("Initialisation des sockets : OK\n");

	struct sockaddr_in server_addr;

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(socket_client, (struct sockaddr *) &server_addr, sizeof(server_addr));
	printf("Connexion au server : OK\n");

	printf("Veuillez entrer le message a envoyer : ");
	fgets(buffer,1024,stdin);

	write(socket_client, buffer, strlen(buffer));
	printf("Envoi du message : OK\n");

	printf("Fermeture des sockets : OK\n");


	return 0;
}