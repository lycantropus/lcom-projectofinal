#include "GenQueue.h"

GQueue * newGQueue(int n_ele, int ele_size) 
{
	GQueue *q = (GQueue *) malloc(sizeof(GQueue));
	q->ptr = malloc(n_ele * ele_size);
	q->in = q->out = q->count = 0;
	q->size = n_ele; q->ele_size = ele_size;
	return q;
}

void deleteGQueue(GQueue *q) 
{
       free(q->ptr); free(q);
}

Bool isEmptyGQueue(GQueue *q)
{
	return (q->count == 0) ? true: false;
}

Bool isFullGQueue(GQueue *q)
{
	return (q->count == q->size) ? true: false;
}

Bool putGQueue(GQueue *q, void *ele) 
{
	if (isFullGQueue(q))
		return false;

	memcpy(q->ptr + q->in, ele, q->ele_size);
	
	q->in = (q->in + q->ele_size);
	++q->count;
	
	return true;
}

void end_of_putGQueue() {}

void * getGQueue(GQueue *q) 
{
	if (isEmptyGQueue(q))
		return NULL;
	void * ret = q->ptr + q->out;
	q->out = (q->out + q->ele_size);
	--q->count;
	return ret;
}
