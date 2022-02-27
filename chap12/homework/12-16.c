/*******************************************************
    > File   : 12-16.c
    > Author : Yuntong
    > Mail   : 171840067@smail.nju.edu.cn
    > Date   : 
*******************************************************/

#include "csapp.h"
void *thread(void *vargp);

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", argv[0]);
		exit(0);
	}
	
	pthread_t tid;
	int i;
	int n = atoi(argv[1]);
	
	for (i = 0; i < n; i++)
		Pthread_create(&tid, NULL, thread, NULL);
	Pthread_exit(NULL);   // main thread wait all peer thread to exit
}

void *thread(void *vargp)
{
	printf("Hello, world!\n");
	return NULL;
}