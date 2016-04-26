/*
 * sbuf.h
 *
 *  Created on: Apr 26, 2016
 *      Author: lizhen
 */
#include "csapp.h"
#ifndef SBUF_H_
#define SBUF_H_
typedef struct{
	int *buf;//buffer array
	int n;// maximum number of slots
	int front;//buf[(front+1)%n]
	int rear;//buf[(rear%n)]
	sem_t mutex;//the protects accesses to buf
	sem_t slots;//counts available slots
	sem_t items;//counts available items
}sbuf_t;

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);

#endif /* SBUF_H_ */
