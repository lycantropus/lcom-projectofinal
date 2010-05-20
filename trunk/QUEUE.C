#include "queue.h"


/** Initialize the queue
*/
void queueInit(Queue *q)
{
	q->in = 0;
	q->out = 0;
	q->cnt = 0;
	q->size = 10;
}

/** Put char 'c' in the queue pointed to by 'q'
* Returns false if operation failed (the queue is full)
*/
Bool queuePut(Queue *q, char c)
{
	if (queueFull(q)) 
	{
		return false;
	}
	
	q->buf[q->in] = c;
	q->cnt++;
	q->in++;
	
	if (q->in >= q->size)	//se ultrapassar os limites do buffer
	{
		q->in = 0;	//volta à posição inicial
	}

	return true;
}

/** Get next element from queue
*  Returns -1 (an int) if there are no elements in the queue
*/
int queueGet(Queue *q)
{
	if (queueEmpty(q)) return -1;
	
	int value = q->buf[q->out];
	
	q->cnt--;
	q->out++;
	
	if (q->out >= q->size)	//se ultrapassar os limites do buffer
	{
		q->out = 0;	//volta à posição inicial
	}
		
	return value;
}
/** Returns true if the queue is empty
*/
Bool queueEmpty(Queue *q)
{
	if (q->cnt == 0)
		return true;
	else
		return false;
}

/** Returns true if the queue if full
*/
Bool queueFull(Queue *q)
{
	return (q->cnt >= q->size);
}

void makeEmpty(Queue *q)
{
	q->in = 0;
	q->out = 0;
	q->cnt = 0;
	q->size = 10;
}
