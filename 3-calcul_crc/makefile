all: exeClient exeServeur

exeServeur: serveur.c commun.h
	gcc -o $@ $^

exeClient: client.c commun.h
	gcc -o $@ $^