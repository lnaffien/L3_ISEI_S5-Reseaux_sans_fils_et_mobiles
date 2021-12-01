all : exe1 exe2

exe1 : 1-thread.c includes.h
	gcc -pthread -o $@ $^

exe2 : 2-mutex.c includes.h
	gcc -pthread -o $@ $^

clean : 
	rm exe*