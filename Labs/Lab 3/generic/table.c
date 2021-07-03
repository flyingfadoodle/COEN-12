

/* Samuel Lim
 *    Coen 12 Lab Project 3
 *       April 2021
 *        */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

//intitialize each function
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)());
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, void *elt);
void removeElement(SET *sp, void *elt);
void *findElement(SET *sp, void *elt);
void *getElements(SET *sp);
static int search(SET *sp, void *elt, bool *found);

typedef struct set { //properties of the set
    void **value;
    int length;
    int count;
    char *flag;
    int (*compare)();
    unsigned (*hash)();
} SET;

//big O notations are at the end of each function, I think they weren't seen in my previous lab and therefore got marked down
//all big O notations are for worse case

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) { //creates hastable
    int i;
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->value = malloc(sizeof(void*)*maxElts);
    sp->flag = malloc(sizeof(void)*maxElts); //now void instead of char
    sp->compare = compare;
    sp->hash = hash;
    assert(sp->value!=NULL && sp->flag!=NULL);
    for(i = 0; i<sp->length; i++) {
        sp->flag[i] = 0;
    }
    return sp;
} // O(n)

void destroySet(SET *sp) { //deallocates memory
    assert(sp!=NULL);
    free(sp->flag);
    free(sp->value);
    free(sp);
} // O(1)

int numElements(SET *sp) { //number of elements in the set
    return sp->count;
} // O(1)

void addElement(SET *sp, void *elt) { //adds element to the set
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (!found) {
        sp->value[position] = elt;
        
        sp->flag[position] = 1;
        sp->count++;
    }
} // O(n)

void removeElement(SET *sp, void *elt) { //removes element from the set
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (found) {
        //free(sp->value[position]);
        sp->flag[position]= 2;
        sp->count--;
    }
} // O(n)

void *findElement(SET *sp, void *elt) { //finds a certain element in the set
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (found) {
        return sp->value[position];
    }
    return NULL;
} // O(n)

void *getElements(SET *sp) { //copies elements in the set
    assert(sp!=NULL);
    char **elts;
    int i, counter;
    
    elts = malloc(sizeof(char*)*(sp->count));
    counter = 0;
    
    for (i = 0; i<sp->length; i++) {
        if (sp->flag[i] == 1) {
            elts[counter] = sp->value[i];
            counter++;
        }
    }
    return elts;
} // O(n)

static int search(SET *sp, void  *elt, bool *found) { //searches for an element using a hash function, then returns the position if it is found, or the position where the element should be
    assert(sp!=NULL && elt!=NULL);
    int i, k, position, temp;
    
    k = -1;
    position = ((*sp->hash)(elt)%sp->length); //now using hash
    
    for (i = 0; i<sp->length; i++) { //cases for found, empty, and deleted
        temp = (position + i)%sp->length;
        
        if (sp->flag[temp] ==  EMPTY) {
            *found = false;
            if (k != -1) {
                return k;
            }
            else {
                return temp;
            }
        }
        
        if (sp->flag[temp] == FILLED) {
            if ((*sp->compare)(elt, sp->value[temp]) == 0) {
                *found = true;
                return temp;
            }
        }
        
        if (sp->flag[temp] == DELETED) {
            if (k == -1) {
                k = temp; 
            }
        }
    }
    *found = false;
    return temp;
} // O(n)

