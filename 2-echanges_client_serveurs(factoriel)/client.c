#include "./commun.h"

int main()
{
	char buffer[BUFFER_TAILLE];

	// Declaration et Initialisation du socket
	int socket_client = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_client < 0)
	{
		printf("Initialisation des sockets : ERREUR\n");
		return errno;
	}
	printf("Initialisation des sockets : OK\n");
	struct sockaddr_in server_addr;
	init_server_addr(&server_addr);

	// Ouverture du socket
	if(connect(socket_client, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
	{
		printf("Connexion au server : ERREUR\n");
		return errno;
	}
	printf("Connexion au server : OK\n");

	// Definition des donnees a envoyer
	printf("Quel est le nombre dont vous voulez connaitre la factoriel ? /!\\ Merci d'en choisir un inferieur pu egal a 16 ! ");
	if(fgets(buffer, BUFFER_TAILLE, stdin) == NULL)
	{
		printf("Enregistrement du message a envoyer : ERREUR\n");
		return errno;
	}
	printf("Vous avez choisi le nombre : %s", buffer);
	printf("Enregistrement du message a envoyer : OK\n");

	// Envoie des donnees
	switch(write(socket_client, &buffer, strlen(buffer)))
	{
		case -1 : 
			printf("Envoi du message : ERREUR\n");
			return errno;
		case 0 :
			printf("Envoi du message : il n'y a rien a envoyer.\n");
			break;
		default :
			printf("Envoi du message : OK\n");
			break;
	}

	// Reinitialisation du buffer
	bzero(buffer, BUFFER_TAILLE);

	socklen_t taille_socket = sizeof(server_addr);
	switch(recvfrom(socket_client, buffer, BUFFER_TAILLE, 0, (struct sockaddr*) &server_addr, &taille_socket))
	{
		case -1 : 
			printf("Reception de la reponse : ERREUR\n");
			return errno;
			break;
		case 0 :
			printf("Reception de la reponse : aucune reponse n'a ete recue\n");
			return errno;
			break;
		default :
			printf("Reception de la reponse : OK\n");
			printf("Message recu : %s\n", buffer);
			break;
	}	

	// Fermeture du socket
	if(close(socket_client) == -1)
	{
		printf("Fermeture du socket : ERREUR\n");
		return errno;
	}
	printf("Fermeture du socket : OK\n");

	return 0;
}