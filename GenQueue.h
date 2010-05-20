#ifndef __GenQUEUE_H
#define __GenQUEUE_H

#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <stdio.h>

#include "utypes.h"


typedef struct 
{
	void *ptr;
	int in, out, count, size, ele_size;
} GQueue;

GQueue * newGQueue(int n_ele, int size_ele);
void deleteGQueue(GQueue *q);
Bool putGQueue(GQueue *q, void *ele);
void * getGQueue(GQueue *q);
Bool isEmptyGQueue(GQueue *q);
Bool isFullGQueue(GQueue *q);

void end_of_putGQueue();

#endif /* __GenQUEUE_H */
