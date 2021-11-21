#include "./commun.h"

int fact(int n)
{
	return n==0 ? 1 : n * (fact (n - 1) );
}

int string_to_int(char * string)
{
	int i = 0, puissance_de_dix = 1, res = 0;
	while (string[i] != '\n')
	{
		if(string[i] >= '0' && string[i] <= '9')
		{
			res *= puissance_de_dix;
			res += string[i] - '0';
			puissance_de_dix *= 10;
		}
		i++;
	}

	return res;	
}

int main()
{
	char buffer[BUFFER_TAILLE];

	// Declaration et Initialisation du socket
	int socket_server = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_server < 0)
	{
		printf("Initialisation des sockets : ERREUR\n");
		return errno;
	}
	printf("Initialisation des sockets : OK\n");

	struct sockaddr_in server_addr;
	init_server_addr(&server_addr);

	// Ouverture du socket en tant que serveur
	if(bind(socket_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
	{
		printf("Bind du socket : ERREUR\n");
		return errno;
	}
	printf("Bind du socket : OK\n");

	// Mise en ecoute du socket cree
	if(listen(socket_server, 5) == -1)
	{
		printf("Mise en ecoute du serveur : ERREUR\n");
		return errno;
	}
	printf("Mise en ecoute du serveur : OK\n");

	// Validation de la connexion
	socklen_t taille_socket = sizeof(server_addr);
	int new_socket_server = accept(socket_server, (struct sockaddr *) &server_addr, &taille_socket);
	if(new_socket_server == -1)
	{
		printf("Validation de la communication : ERREUR\n");
		return errno;
	}
	printf("Validation de la communication : OK\n");

	// Lecture des donnees
	if(read(new_socket_server, &buffer, BUFFER_TAILLE) == -1)
	{
		printf("Reception du message : ERREUR\n");
		return errno;
	}
	printf("Reception du message : OK\n");
	printf("Message recu : %s\n", buffer);

	// Transformation de la chaine de caracteres recue en un nombre
	int nbr = string_to_int(buffer);
	printf("Transformation de la chaine recue en un nombre : OK\n");

	// Reinitialisation du buffer
	bzero(buffer, BUFFER_TAILLE);
	printf("Reinitialisation du buffer : OK\n"); //TO-DO : fonction pour vérifier que le buffer soit vide

	// Calcul de la factorielle du nombre recu
	sprintf(buffer, "%d", fact(nbr));
	printf("Calcul de la factorielle : OK\n");	
	printf("Resultat : %d! = %s\n", nbr, buffer);

	// Envoie du resultat
	if(sendto(new_socket_server, buffer, BUFFER_TAILLE, 0, (struct sockaddr*) &server_addr, taille_socket) == -1)
	{
		printf("Envoi de la reponse : ERREUR : %d\n", errno);
		return errno;
	}
	printf("Envoi de la reponse : OK\n");
	printf("Message envoyé : %s\n", buffer);
	
	// Fermeture du socket
	if(close(new_socket_server) == -1)
	{
		printf("Fermeture du socket : ERREUR\n");
		return errno;
	}
	printf("Fermeture du socket : OK\n");

	return 0;
}