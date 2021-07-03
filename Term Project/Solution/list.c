/* Samuel Lim
 * Coen 12 Term Project
 * June 2021
 */

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

#define maxElements 8

typedef struct node { //node structure
    struct node *next;
    struct node *prev;
    void **value;
    int firstIndex;
    int count;
    int size;
} NODE;

typedef struct list { //list structure
    NODE *head;
    NODE *tail;
    int count;
} LIST;

// Big O values are at the end of each function

//intialize functions
LIST *createList(void);
void destroyList(LIST *lp);
int numItems(LIST *lp);
void addFirst(LIST *lp, void *item);
void addLast(LIST *lp, void *item);
void *removeFirst(LIST *lp);
void *removeLast(LIST *lp);
void *getItem(LIST *lp, int index);
void setItem(LIST *lp, int index, void *item);

LIST *createList(void) { //creates list, intial node and its components
    LIST *lp;
    NODE *new;
    
    lp = malloc(sizeof(LIST));
    assert(lp!=NULL);
    
    new = malloc(sizeof(NODE));
    assert(new != NULL);
    
    new->next = NULL;
    new->prev = NULL;
    new->value = malloc(sizeof(void*) * maxElements);
    assert(new->value != NULL);
    new->firstIndex = 0; //index to determine where to put item
    new->count = 0;
    new->size = maxElements; //intital size is deteremined by pre-set maxElements 
    
    lp->count = 0;
    lp->head = new;
    lp->tail = lp->head;
    
    return lp;
} // O(1) 

void destroyList(LIST *lp) { //destroys list, freeing all allocations
    assert (lp != NULL);
    NODE *temp, *next;
    
    temp = lp->head;
    while (temp != NULL) {
        next = temp->next;
        free(temp->value); //free value before freeing the node
        free(temp);
        temp = next;
    }
    free(lp); //free entire list once contents are gone
} // O (n)

int numItems(LIST *lp) { //returns total items in the list
    assert(lp != NULL);
    return lp->count;
} // O(1)

void addFirst(LIST *lp, void *item) { //add item in the first node in the list
    assert(lp != NULL);
    NODE *new;
    int index, length;
    
    if (lp->head->count == lp->head->size) { //checks if array is full
        if (lp->count/2 < maxElements) {
            length = maxElements;
        }
        else {
            length = lp->count/2;
        }
        length = lp->head->size*2;
        
        new = malloc(sizeof(NODE)); //create new node to insert item into
        assert(new != NULL);
        
        new->next = NULL;
        new->prev = NULL;
        new->value = malloc(sizeof(void*) * length);
        assert(new->value != NULL);
        new->firstIndex = 0;
        new->count = 0;
        new->size = length; //new length
        
        lp->head->prev = new; //new first node
        lp->head->prev->next = lp->head;
        lp->head = lp->head->prev;
    }
    index = lp->head->firstIndex - 1; //if array isn't full then insert item into the free space
    if (index < 0) {
        index = lp->head->size - 1;
    }
    lp->head->value[index] = item;
    lp->head->firstIndex = index;
    lp->head->count++;
    lp->count++; //increment important values
} // O(1)

void addLast(LIST *lp, void *item) { //add item in the last node in the list
    assert(lp!=NULL);
    NODE *new;
    int index, length;
    
    if (lp->tail->count == lp->tail->size) { //checks if array is full 
        if (lp->count/2 < maxElements) {
            length = maxElements;
        }
        else {
            length = lp->count/2; //similar process to addFirst
        }
        new = malloc(sizeof(NODE)); //create new node to insert item into
        assert(new != NULL);
        
        new->next = NULL;
        new->prev = NULL;
        new->value = malloc(sizeof(void*) * length);
        assert(new->value != NULL);
        new->firstIndex = 0;
        new->count = 0;
        new->size = length; //new length
       
        lp->tail->next = new; //new last node
        lp->tail->next->prev = lp->tail;
        lp->tail = lp->tail->next;
    }
    index = lp->tail->firstIndex + lp->tail->count; //if array isn't full then insert item into the free space
    if (index >= lp->tail->size) {
        index = lp->tail->size-index;
    }
    lp->tail->value[index] = item;
    lp->tail->count++;
    lp->count++; //increment important values
} // O(1)

void *removeFirst(LIST *lp) { //removes item from array from the first node
    assert(lp != NULL && lp->count > 0);
    void *tempValue;
    
    if (lp->head->count == 0) { //removes node if there isn't any items in array
        lp->head = lp->head->next;
        free(lp->head->prev);
        lp->head->prev = NULL;
    }
    tempValue = lp->head->value[lp->head->firstIndex];
    if (++ lp->head->firstIndex == lp->head->size) {
        lp->head->firstIndex = 0;
    }
    lp->head->count--;
    lp->count--; //adjust important values
    return tempValue; //return the value
} // O(1)

void *removeLast(LIST *lp) { //removes item from array from the last node
    assert(lp != NULL && lp->count > 0);
    int index;
    void *tempValue;
    
    if (lp->tail->count == 0) { //removes node if there isn't any items in array
        lp->tail = lp->tail->prev;
        free(lp->tail->next);
        lp->tail->next = NULL;
    }
    index = lp->tail->firstIndex + lp->tail->count - 1;
    if (index >= lp->tail->size) {
        index -= lp->tail->size;
    }
    tempValue = lp->tail->value[index];
    lp->tail->count--;
    lp->count--; //adjust important values
    return tempValue; //return the value
} // O(1)

void *getItem(LIST *lp, int index) { //returns the item at the given index
    assert(lp != NULL && index >= 0);
    NODE *temp;
    
    temp = lp->head;
    while (index >= temp->count) { //if the given index is greater than the number of items in the node
        index -= temp->count; //adjust index value to find the correct item
        temp = temp->next;
    }
    index += temp->firstIndex;
    if (index >= temp->size) {
        index -= temp->size;
    }
    return temp->value[index]; //return the value at adjusted index and correct node
} // O(n)

void setItem(LIST *lp, int index, void *item) { //searches for item at the given index, then gives that item the new given value
    assert(lp != NULL && index >= 0 && index < lp->count);
    NODE *temp;
    
    temp = lp->head;
    while (index >= temp->count) { //same as from getItem
        index -= temp->count;
        temp = temp->next;
    }
        temp->value[index] = item; //"set" the value
} // O(n)
