#include "./commun.h"

int main()
{
	char buffer[1024];
	int socket_server = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_server < 0)
	{
		printf("Initialisation des sockets : ERREUR\n");
		return errno;
	}
	printf("Initialisation des sockets : OK\n");

	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(socket_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
	{
		printf("Bind du socket : ERREUR\n");
		return errno;
	}
	printf("Bind du socket : OK\n");

	if(listen(socket_server, 5) == -1)
	{
		printf("Mise en ecoute du serveur : ERREUR\n");
		return errno;
	}
	printf("Mise en ecoute du serveur : OK\n");

	socklen_t taille_socket = sizeof(server_addr);
	int new_socket_server = accept(socket_server, (struct sockaddr *) &server_addr, &taille_socket);
	if(new_socket_server == -1)
	{
		printf("Validation de la communication : ERREUR\n");
		return errno;
	}
	printf("Validation de la communication : OK\n");

	//lecture des donnees
	if(read(new_socket_server, &buffer, 1024) == -1)
	{
		printf("Reception du message : ERREUR\n");
		return errno;
	}
	printf("Reception du message : OK\n");

	printf("Message recu : %s", buffer);

	bzero(buffer, 1024); //reinitialisation du buffer
	printf("Reinitialisation du buffer : OK\n"); //TO-DO : fonction pour vérifier que le buffer soit vide

	if(close(new_socket_server) == -1)
	{
		printf("Fermeture du socket : ERREUR\n");
		return errno;
	}
	printf("Fermeture du socket : OK\n");

	return 0;
}