/*
 * main.c
 *
 *  Created on: Apr 21, 2016
 *      Author: lizhen
 */
#include "csapp.h"
#include "sbuf.h"
#define NTHREADS 4
#define SBUFSIZE 16

void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf;//shared buffer of connected descriptions;
			//连接的共享buf的描述符

int main(int argc,char* argv[]){
	int i;
	int listenfd;//监听描述符
	int connfd;//连接描述符
	int port;//端口

	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	pthread_t tid;

	if(argc != 2){
		fprintf(stderr,"usage: %s <port>\n",argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	sbuf_init(&sbuf,SBUFSIZE);//对sbuf进行初始化，设置buf的大小为BUFSIZE=16
	listenfd = Open_listenfd(port);

	for(i = 0;i<NTHREADS;i++){
		Pthread_create(&tid,NULL,thread,NULL);//创造一组工作者线程
	}

	while(1){
		connfd = Accept(listenfd,(SA*) &clientaddr,&clientlen);//接受连接请求
		sbuf_insert(&sbuf,connfd);//将连接线程插入到缓冲区sbuf中
	}
	return 0;
}

void *thread(void *vargp){
	Pthread_detach(pthread_self());//每个工作者线程，都对自己进行分离，因为web服务器对每个连接都会产生一个单独的线程
		//但是服务器不会等待每个单独的线程终止stop，因此每个对等线程应该在它开始处理请求之前分离它自身
	while(1){
		int connfd = sbuf_remove(&sbuf);//每个线程等待，直到它能够从缓冲区中取出一个已连接描述符
		echo_cnt(connfd);//利用connfd，调用echo_cnt函数向客户端  回送  客户端的输入
		Close(connfd);//关闭连接描述符
	}
}
