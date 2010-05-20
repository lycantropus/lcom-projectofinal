#ifndef __QUEUE_H
#define __QUEUE_H

#include <pc.h>
#include <go32.h>
#include <dpmi.h>
#include <dos.h>

#include "utypes.h"
#include "music.h"

/** @defgroup queue Queue
 * @{
 *
 * Queue related functions
 */

/** Queue definition
 */
typedef struct {
    char buf[10]; 	///< array which the queue is based on
    int in;			///< index on array where to put next element
    int out;		///< index on array where to get next element from
    int cnt;		///< current number of elements in the queue
    int size;		///< queue capacity
} Queue;

/** Initialize the queue
*/
void queueInit(Queue *q);

/** Put char 'c' in the queue pointed to by 'q'
* Returns false if operation failed (the queue is full)
*/
Bool queuePut(Queue *q, char c);

/** Get next element from queue
*  Returns -1 (an int) if there are no elements in the queue
*/
int queueGet(Queue *q);

/** Returns true if the queue is empty
*/
Bool queueEmpty(Queue *q);

/** Returns true if the queue if full
*/
Bool queueFull(Queue *q);

void makeEmpty(Queue *q);

#endif /* __QUEUE_H */
