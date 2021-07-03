/* Samuel Lim
   Coen 12 Project 2
   April 18 2021
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

SET *createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);
static int search(SET *sp, char *elt, bool *found);

typedef struct set { //defines properties of set
    char** value;
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
    
    for (i = 0; i < sp->count; i++) { //looping through set
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
    int i, position;
    bool found;
    found = false;
    position = search(sp, elt, &found);
    
    if (!found) { //same as found == false
        for (i = sp->count; i >= position; i--) { //looping backwards
            sp->value[i] = sp->value[i-1];
        }
        sp->value[position] = strdup(elt);
        sp->count++;
    }
} //Big O of O(n)

void removeElement(SET *sp, char *elt) { //removes element from array
    assert(sp!=NULL);
    int i, position;
    bool found;
    found = false;
    position = search(sp, elt, &found);
    
    if (found) {
        free(sp->value[position]);
        for (i = position; i < sp->count-1; i++) {
            sp->value[i] = sp->value[i+1];
        }
        sp->count--;
    }
} //Big O of O(n)

char *findElement(SET *sp, char *elt) { //returns element if it is found
    assert(sp!=NULL);
    bool found;
    int position;
    found = false;
    position = search(sp, elt, &found);
    
    if(found) { //same as found == true
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

static int search(SET *sp, char *elt, bool *found) { //searches for given element and returns position if found
    assert(sp!=NULL);
    assert(elt!=NULL);
    int low, middle, high;
    low = 0;
    high = sp->count-1;
    
    while (low<=high) {
        middle = (low+high)/2; //because we can assume this is "sorted", we can cut down on the runtime
        if (strcmp(elt, sp->value[middle]) < 0) {
            high = middle-1;
        }
        else if (strcmp(elt, sp->value[middle]) > 0) {
            low = middle+1;
        }
        else {
            *found = true;
            return middle;
        }
    }
    *found = false;
    return low;
} //Big O of O(n)
