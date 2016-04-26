/*
 * sbuf.c
 *
 *  Created on: Apr 26, 2016
 *      Author: lizhen
 */
#include "sbuf.h"
#include "csapp.h"
/*简单的生产者-消费者缓冲池
 * */
void sbuf_init(sbuf_t *sp,int n){
	sp->buf = Calloc(n,sizeof(int));
	sp->n = n;
	sp->front = sp->rear = 0;//设置front和rear表示一个空的buf
	Sem_init(&sp->mutex,0,1);//对mutex,slots,items三个信号量赋初始值
	Sem_init(&sp->slots,0,n);
	Sem_init(&sp->items,0,0);
}

void sbuf_deinit(sbuf_t *sp){
	//当应用程序使用完缓冲区，释放缓冲区存储的
	Free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item){
	//等待一个可用的槽位，
	//对互斥锁加锁，添加元素，对互斥锁解锁
	//然后宣布有一个新元素可用了
	P(&sp->slots);//等待可用的槽位
	P(&sp->mutex);//对互斥锁加锁
	sp->rear++;
	sp->buf[(sp->rear)%(sp->n)] = item;//添加元素
	V(&sp->mutex);//对互斥锁解锁
	V(&sp->items);//宣布有一个新的元素可以使用了
}

int sbuf_remove(sbuf_t *sp){
	/*sbuf_remove()与sbuf_insert()对称的，
	 * 在等待一个可用的缓冲区元素之后，
	 * 对互斥锁加锁，从缓冲区的前面取出该元素，对互斥锁解锁，
	 * 然后发出信号通知一个新的槽位可用了
	 * */
	P(&sp->items);//等待一个可用的缓冲区元素
	P(&sp->mutex);//对互斥锁加锁
	sp->front++;//找到buf中的第一个元素
	int item = sp->buf[(sp->front)%(sp->n)];//从buf中取走第一个元素
	V(&sp->mutex);//对互斥锁解锁
	V(&sp->slots);//宣布buf中又有一个空的位置了

	return item;
}




