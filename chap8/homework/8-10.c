/*******************************************************
    > File   : 8-10.c
    > Author : Yuntong
    > Mail   : 171840067@smail.nju.edu.cn
    > Date   : 
*******************************************************/

#include "../csapp.h"


int main(){
	int i;

	for (i=0;i<2;i++){
		fork();
	}
	printf("hello\n");
	exit(0);
}