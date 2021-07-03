/* Samuel Lim
   Coen 12 Project 2
   April 18 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>

SET *createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);

typedef struct set { //defines properties of set
    char **value;
    int length;
    int count;
} SET;


SET *createSet(int maxElts) { //allocates memory to create a set
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->value = malloc(sizeof(char*)*maxElts);
    assert(sp->value!=NULL);
    return sp;
} //Big O of O(n)

void destroySet(SET *sp) { //frees each allocation to destroy the set
    assert(sp!=NULL);
    int i;
    
    for (i = 0; i < sp->count; i++) {
        free(sp->value[i]);
    }
    free(sp->value);
    free(sp);
} //Big O of O(n)

int numElements(SET *sp) { //returns the number of elements
    return sp->count;
} //Big O of O(1)

void addElement(SET *sp, char *elt) { //adds element to array
    assert(sp!=NULL);
    int difference;
    difference = search(sp, elt);
    
    if (difference == -1) {
        sp->value[sp->count]=strdup(elt);
        assert(sp->value[sp->count]!=NULL);
        sp->count++;
    }
} //Big O of O(1)

void removeElement(SET *sp, char *elt) { //removes element from array
    assert(sp!=NULL);
    int position;
    position = search(sp, elt);
    
    if(position >= 0) {
        free(sp->value[position]);
        sp->value[position] = sp->value[sp->count-1];
        sp->count--;
    }
} //Big O of O(1)

char *findElement(SET *sp, char *elt) { //returns element if it is found
    assert(sp!=NULL);
    int position;
    position = search(sp, elt);
    
    if(position >= 0) {
        return sp->value[position];
    }
    else {
        return NULL;
    }
} //Big O of O(1)

char** getElements(SET *sp) { //allocates memory and returns the copy of the set
    assert(sp!=NULL);
    int i;
    char **array;
    array = malloc(sizeof(char *)*(sp->count));
    
    for (i = 0; i < sp->count; i++) {
        array[i] = sp->value[i];
    }
    return array;
} //Big O of O(n)

static int search(SET *sp, char *elt) { //searches for given element and returns position if found
    assert(sp!=NULL);
    int i, difference;
    i = 0;
    
    while (i < sp->count) {
        difference = strcmp(elt, sp->value[i]);
        
        if (difference == 0) {
            return i;
        }
        i++;
    }
    return -1;
} //Big O of O(n)
