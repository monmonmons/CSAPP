/*******************************************************
    > File   : 8-11.c
    > Author : Yuntong
    > Mail   : 171840067@smail.nju.edu.cn
    > Date   : 
*******************************************************/

#include "../csapp.h"

void doit(){
	fork();
	fork();
	printf("hello\n");
	return;
}

int main(){
	doit();
	printf("hello\n");
	exit(0);
}
