/*
 * main.c
 *
 *  Created on: Apr 21, 2016
 *      Author: lizhen
 */
#include <stdio.h>
#include "csapp.h"

int main(int argc,char* argv[]){
	char **pp;
	struct in_addr addr;//network net_ip
	struct hostent *hostp;//dns主机条目结构
	if(argc != 2){
		printf("error,usage: %s <domain name or dotted-decimal>\n",argv[0]);
		exit(0);
	}

	if(inet_aton(argv[1],&addr)){
		//判断是否将点分十进制---->十六进制网络序
		hostp = gethostbyaddr((const char *) &addr,sizeof(addr),AF_INET);
	}else{
		hostp = gethostbyname(argv[1]);
	}

	for(pp = hostp->h_aliases;*pp!=NULL;pp++){
		printf("alias: %s\n",*pp);
	}

	for(pp = hostp->h_addr_list;*pp!=NULL;pp++){
		addr.s_addr = ((struct in_addr*) *pp)->s_addr;
		printf("address: %s\n",inet_ntoa(addr));
	}

}



