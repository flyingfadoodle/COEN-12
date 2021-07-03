

/* Samuel Lim
 *    Coen 12 Project 5
 *       May 2021
 *        */

#include "pqueue.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct pqueue {
    void** value;
    int count;
    int length;
    int (*compare)();
} PQ;

//big O notation at the end of each function

PQ *createQueue(int (*compare)()) { //create priority queue
    PQ *pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->value = malloc(sizeof(void*)*10);
    pq->count = 0;
    pq->length = 10;
    pq->compare = compare;
    assert(pq->value != NULL);
    return pq;
} // O(1)

void destroyQueue(PQ *pq) { //destorys the queue
    assert(pq != NULL);
    int i;
    
    free(pq->value);
    free(pq);
} // O(n)

int numEntries(PQ *pq) { //returns number of integers in the queue
    assert(pq != NULL);
    return pq->count;
} // O(1)

void addEntry(PQ *pq, void *entry) { //inserts the entry into queue
    assert(pq != NULL);
    int parent, child;
    void *temp;
    
    if (pq->count == pq->length) {
        pq->length *= 2;
        pq->value = realloc(pq->value, sizeof(void*) *pq->length); //double array size
    }
    pq->value[pq->count] = entry;
    parent = (pq->count-1)/2;
    child = pq->count;
    
    while ((*pq->compare)(pq->value[child],pq->value[parent]) == -1) { //compares value of child to parent
        temp = pq->value[parent]; //save data of parent
        pq->value[parent] = pq->value[child]; //data swap
        pq->value[child] = temp; //data swap
        child = parent; //swap index
        parent = (parent-1)/2; //formula to reach root
    }
    pq->count++;
} // O(logn)

void *removeEntry(PQ *pq) { //remove from queue
    assert(pq != NULL);
    int position, leftChild;
    void* toDelete,* temp;
    
    position = 0;
    toDelete = pq->value[0];
    pq->value[0] = pq->value[pq->count - 1]; //swaps root with last item in heap
    
    while(((position*2)+2) <= pq->count - 1) {
        leftChild = (position*2)+1; //stores left child index 
        
        if ((position*2+2) <= pq->count-1) {
            if ((*pq->compare)(pq->value[(position*2)+2], pq->value[(position*2)+1]) < 0) { //compares right child and left child and sees which is smaller
                leftChild = (position*2)+2;
            }
        }
        if ((*pq->compare)(pq->value[position], pq->value[leftChild]) < 0) { //checks if parent is smaller than its children
            break; //exits out
        }
        else { //swapping
            temp = pq->value[position];
            pq->value[position] = pq->value[leftChild];
            pq->value[leftChild] = temp;
        }
        position = leftChild;
    }
    pq->count--; //decrease at end, only if one was removed
    return toDelete;
} // O(logn)

