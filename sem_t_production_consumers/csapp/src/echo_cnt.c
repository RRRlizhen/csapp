/*
 * echo_cnt.c
 *
 *  Created on: Apr 26, 2016
 *      Author: lizhen
 */
#include "csapp.h"
static int byte_cnt;//全局变量，记录从所有客户端接收到的累计字节数
static sem_t mutex;

static void init_echo_cnt(void){
	Sem_init(&mutex,0,1);
	byte_cnt = 0;
}

void echo_cnt(int connfd){
	int n;
	char buf[MAXLINE];
	rio_t rio;
	static pthread_once_t once = PTHREAD_ONCE_INIT;


	Pthread_once(&once, init_echo_cnt);
	Rio_readinitb(&rio,connfd);//初始化RIO带缓冲区的I/O包
	while((n = Rio_readlineb(&rio,buf,MAXLINE)) != 0){
		P(&mutex);
		byte_cnt += n;
		printf("thread %d received %d (%d total) bytes on fd %d\n",
				(int) pthread_self(),n,byte_cnt,connfd);
		V(&mutex);
		Rio_writen(connfd,buf,n);//想客户端回送 接收 的每一个文本行
	}
}
