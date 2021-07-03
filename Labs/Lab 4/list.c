



/* Samuel Lim
 *    Coen 12 Lab
 *       May 2021
 *        */

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

typedef struct node {
    void* value;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list {
    int count;
    NODE *head;
    int (*compare)();
} LIST;

LIST *createList(int (*compare)());
void destroyList(LIST *lp);
int numItems(LIST *lp);
void addFirst(LIST *lp, void *item);
void addLast(LIST *lp, void *item);
void *removeFirst(LIST *lp);
void *removeLast(LIST *lp);
void *getFirst(LIST *lp);
void *getLast(LIST *lp);
void removeItem(LIST *lp, void *item);
void *findItem(LIST *lp, void *item);
void *getItems(LIST *lp);


//big O notation is at end of each function

LIST *createList(int (*compare)()) { //creates list and intializes variables
    LIST *lp;
    NODE *temp;
    lp = malloc(sizeof(LIST));
    assert(lp!=NULL);
    lp->count = 0;
    temp = malloc(sizeof(NODE));
    assert(temp!=NULL);
    temp->next=temp;
    temp->prev=temp;
    lp->head=temp;
    lp->compare=compare;
    return lp;
} // O(1)

void destroyList(LIST *lp) { //destroys list, freeing all allocations
    assert (lp != NULL);
    NODE *np, *dp;
    
    dp = lp->head;
    np = dp->next;
    while (np != lp->head) {
        free(dp);
        dp = np;
        np = np->next;
    }
} // O(n)

int numItems(LIST *lp) { //returns number of items in list
    assert(lp!=NULL);
    return lp->count;
} // O(1)

void addFirst(LIST *lp, void *item) { //add item as the first node in the list
    assert(lp!=NULL);
    NODE *new;
    
    new = malloc(sizeof(NODE));
    new->next = lp->head->next;
    new->prev = lp->head;
    new->next->prev = new;
    lp->head->next = new;
    new->value = item;
    lp->count++;
} // O(1)

void addLast(LIST *lp, void *item) { //add item as the last node in the list
    assert(lp!=NULL);
    NODE *new, *np;
    
    new = malloc(sizeof(NODE));
    np = lp->head->prev;
    new->next=lp->head;
    new->prev = np;
    np->next = new;
    lp->head->prev = new;
    new->value = item;
    lp->count++;
} // O(1)

void *removeFirst(LIST *lp) { //removes the first item in the list
    assert(lp!=NULL && lp->count>0);
    NODE *temp;
    void* tempValue;    

    temp = lp->head->next;
    lp->head->next = temp->next;
    temp->next->prev = lp->head;
    lp->count--;
    tempValue = temp->value;
    free(temp);
    return tempValue;
} // O(1)

void *removeLast(LIST *lp) { //removes the last item in the list
    assert(lp!=NULL && lp->count>0);
    NODE *temp;
    void* tempValue; 
   
    temp = malloc(sizeof(NODE));
    temp = lp->head->prev;
    lp->head->prev = temp->prev;
    temp->prev->next = lp->head;
    lp->count--;
    tempValue = temp->value;
    free(temp);
    return tempValue;
} // O(1)

void *getFirst(LIST *lp) { //returns the first item in the list
    assert(lp!=NULL && lp->count>0);
    return lp->head->next->value;
} // O(1)

void *getLast(LIST *lp) { //returns the last item in the list
    assert(lp!=NULL && lp->count>0);
    return lp->head->prev->value;
} // O(1)

void removeItem(LIST *lp, void *item) { //seraches for the given item and removes it
    assert(lp!=NULL && lp->compare!=NULL);
    NODE *np;
    int difference;
    
    np = lp->head;
    while (np->next != lp->head) {
        np = np->next;
        difference = (*lp->compare)(item, np->value);
        if (difference == 0) {
            np->next->prev = np->prev;
            np->prev->next = np->next;
            lp->count--;
            free(np);
            return;
        }
    }
    return;
} //O(n)
    
void *findItem(LIST *lp, void *item) { //searches for an item and returns it, else returns NULL
    assert(lp!=NULL && lp->compare!=NULL);
    NODE *np;
    int difference;
    
    np = lp->head;
    while (np->next != lp->head) {
        np = np->next;
        difference = (*lp->compare)(item, np->value);
        if (difference == 0)
            return np->value;
    }
    return NULL;
} // O(n)

void *getItems(LIST *lp) { //returns array of all items
    assert(lp != NULL);
    void **elts;
    NODE *p;
    int i;
    
    elts = malloc(sizeof(void*)*lp->count);
    p = lp->head->next;
    for (i = 0; i<lp->count; i++) {
        elts[i] = p->value;
        p = p->next;
    }
    return elts;
} // O(n)

