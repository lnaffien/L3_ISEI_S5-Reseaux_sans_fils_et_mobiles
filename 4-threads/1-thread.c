#include "includes.h"

void *thread_fonction(void *arg)
{
    int nbr = *(&arg);  
    nbr ++;
    printf("%d\n", nbr);
    pthread_exit(nbr);
}

int main()
{
    int nbr;
    printf("Quel nombre voulez-vous incrementer ? Merci de prendre un nombre >= %d et < %d\n", INT_MIN - 1, INT_MAX);
    scanf("%d", &nbr);

    if(nbr > INT_MAX - 1|| nbr <= INT_MIN)
    {
        printf("Hey, si il y a un intervalle c'est pas pour rien ! Tant pis pour toi, maintenant tu dois tout recommencer !\n");
        return EXIT_FAILURE;
    }

    // Lancement du thread
    pthread_t thread;
    void * ptr_nbr = nbr;
    int i = *(&ptr_nbr + 0);
    printf("%d\n", i);
    if(pthread_create(&thread, NULL, thread_fonction, ptr_nbr) != 0)
    {
        printf("Creation du thread : ERREUR\n");
        return EXIT_FAILURE;
    };
    printf("Creation du thread : OK\n");

    // Attente du resultat
    printf("En attente du thread...\n");
    void ** ptr_new_nbr_void;
    if(pthread_join(thread, ptr_new_nbr_void) != 0)
    {
        printf("Attente du thread : %d\n", errno);
        return EXIT_FAILURE;
    }

    // Affichage du resultat
    int ptr_new_nbr_int = *((int *)ptr_new_nbr_void);
    printf("Thread fini !\n");
    printf("Resultat : %d + 1 = %d\n", nbr, ptr_new_nbr_int);

    return EXIT_SUCCESS;
}