/*
 * main.c
 *
 *  Created on: Apr 21, 2016
 *      Author: lizhen
 */
#include <stdio.h>
#include "csapp.h"

int main(int argc,char* argv[]){
	struct in_addr inaddr;//addr in network byte order
	unsigned int addr;//addr in host byte order
	char *str;

	if(argc != 2){
		fprintf(stderr,"usage: %s <hex number>\n",argv[0]);
	}
	sscanf(argv[1],"%x",&addr);
	inaddr.s_addr = htonl(addr);//将host byte order->addr in network byte order
	str = inet_ntoa(inaddr);
	printf("%s\n",str);
	return 0;
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



