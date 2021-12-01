#include "includes.h"

#define NBR_THREADS 4

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // ou phtread_mutex_init(&mutex, NULL);
int val_partagee;

void *thread_fonction(void *arg)
{ 
    // Verrouillage de la zone critique
    if(pthread_mutex_lock(&mutex) != 0)
    {
        printf("Verrouillage de la zone critique : ERREUR : %d\n", errno);
        return 0;
    }
    printf("Verrouillage de la zone critique : OK\n");

    // Incrementation de la variable partagee
    for(int i = 0; i < 10000; i++)
    {
        val_partagee++;
    }

    // Deverrouillage de la zone critique
    if(pthread_mutex_unlock(&mutex) != 0)
    {
        printf("Deverrouillage de la zone critique : ERREUR : %d\n", errno);
        return 0;
    }
    printf("Deverrouillage de la zone critique : OK\n");

    pthread_exit(0);
}

int main()
{
    pthread_t thread_generator[NBR_THREADS];
    val_partagee = 0;

    // Lancement des threads
    for(int i = 0; i < NBR_THREADS; i++)
    {
        if(pthread_create(&thread_generator[i], NULL, thread_fonction, NULL) != 0)
        {
            printf("Creation du thread %d : ERREUR : %d\n", i + 1, errno);
            return EXIT_FAILURE;
        }
        printf("Creation du thread %d : OK\n", (i + 1));
    }
    
    printf("Mise en attente des threads\n");

    // Attente de la fin de tous les threads
    for(int i = 0; i < NBR_THREADS; i++)
    {
        if(pthread_join(thread_generator[i], NULL) != 0)
        {
            printf("Attente du thread %d : ERREUR : %d\n", i + 1, errno);
            return EXIT_FAILURE;
        }
        printf("Attente du thread %d : OK\n", i + 1);
    }

    // Affichage de la variable partagee inrementee
    printf("%d\n", val_partagee);

    return EXIT_SUCCESS;
}