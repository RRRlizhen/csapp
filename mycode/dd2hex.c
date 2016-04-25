/*
 * main.c
 *
 *  Created on: Apr 21, 2016
 *      Author: lizhen
 */
#include <stdio.h>
#include "csapp.h"

int main(int argc,char* argv[]){
	//--------------------------
	struct in_addr my_inaddr;//addr in network byte order
	unsigned int my_addr;//add in host byte order

	if(argc != 2){
		fprintf(stderr,"usage: %s <dd address>\n",argv[0]);
		exit(0);
	}

	if(inet_aton(argv[1],&my_inaddr) == 0){
		printf("inet_aton error\n");
		exit(0);
	}else{
		my_addr = ntohl(my_inaddr.s_addr);
		printf("0x%x\n",my_addr);
	}
}

/*
 * 	const char *mycp = NULL;
	char *str;
	struct in_addr myip_addr;

	//十六进制->点分十进制
	scanf("%x",&myip_addr.s_addr);
	str = inet_ntoa(myip_addr);
	printf("%s",*str);
 * */



