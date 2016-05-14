/*************************************************************************
    > File Name: producer_and_consumer.c
    > Author: lizhen
    > Mail: lizhen_ok@163.com 
    > Created Time: Thu 28 Apr 2016 05:43:14 PM CST
 ************************************************************************/

#include<stdio.h>
typedef struct{
	int *buf;//buffer array
	int n;//maximum nubmer of slots
	int front;//buf[(font+1)%n] is the first item
	int rear;//buf[(font%n)] is last item
	sem_t mutex;//protect acesses to buf
	sem_t slots;//counts avaiable slots
	sem_t items;//counts avaiable item
} sbuf_t;

void sbuf_init(sbuf_t *sp,int n){
	sp->buf = calloc(n,sizeof(int));
	sp->n = n;
	sp->front = sp->rear = 0;
	Sem_init(&sp->mutex,0,1);
	Sem_init(&sp->slots,0,n);
	Sem_init(&sp->items,0,0);
}

void sbuf_deinit(sbuf_t *sp){
	Free(sp->buf);
}

//insert item onto the rear of shared buffer sp
void sbuf_insert(sbuf_t *sp,int item){
	P(&sp->slots);
	P(&sp->mutex);
	sp->buf[(++sp->rear)%(sp->n)] = item;
	V(&sp->mutex);
	V(&sp->items);
}

int sbuf_remove(sbuf_t *sp){
	int item;
	P(&sp->item);
	P(&sp->mutex);
	item = sp->buf[(++sp->front)%(sp->n)];
	V(&sp->mutex);
	V(&sp->slots);
	return item;
}
//##########################读者优先的策略
int readcnt;
sem_t mutex,w;
/*
 * 信号量w控制对访问共享对象的临界区的访问
 * 信号量mutex保护对共享变量readcnt的访问
*/
readcnt = 0;
sem_init(&mutex,0,1);
sem_init(&w,0,1);
void reader(void){
	while(1){
		P(&mutex);
		readcnt++;
		if(readcnt == 1){
			P(&w);
		}
		V(&mutex);
		
		//critical section
		//reading happens
		P(&mutex);
		readcnt--;
		if(readcnt == 0){
			V(&w);
		}
		V(&mutex);
	}//while
}

void writer(void){
	while(1){
		P(&w);
		//critical section
		//writing happens
		V(&w);
	}
}
//############################################

//###############################写者优先的策略
int readcnt = 0;
semt_t mutex;
semt_t rw;//用来保证读者和写着互斥地访问文件
semt_t first_w;//用于实现写优先
sem_init(&mutex,0,1);
sem_init(&w,0,1);
sem_init(&fw,0,1);

void writer(){
	while(1){
		P(&first_w);//在无写进程请求时进入
		P(&rw);//互斥访问文件
//		critical setion
		printf("writing\n");
		V(&rw);//释放共享文件
		V(&first_w);//恢复对共享文件的访问
	}
}

void read(){
	while(1){
		P(&first_w);//在无写进程请求进入
		P(&mutex);//互斥访问readcnt变量

		if(readcnt==0){
			P(rw);//阻止写进程写
		}
		readcnt++;
		V(&mutex);
		V(&frist_w);//恢复对共享文件的访问
		//critical section
		printf("reading\n");
		P(&mutex);//互斥访问readcnt
		readcnt--;

		if(readcnt==0){
			V(&rw);//允许写进程写
		}

		V(&mutex);//释放互斥变量readcnt
	}
}
//##################--------------
