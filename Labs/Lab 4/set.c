/* Samuel Lim
 * Coen 12 Project 4
 * May 2021
 */

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "set.h"

struct set {
    int count;
    int length;
    LIST  **value;
    int (*compare)();
    unsigned (*hash)();
} ;

//big O values are at the end of each function

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) { //creates set
    SET *sp = malloc(sizeof(SET));
    int i;
    assert(sp!=NULL);
    sp->length=maxElts/20;
    sp->count=0;
    sp->hash=hash;
    sp->compare=compare;
    sp->value=malloc(sizeof(LIST*) * sp->length);
    for (i = 0; i<sp->length; i++) {
        sp->value[i]=createList(compare);
    }
    assert(sp->value!= NULL);
    return sp;
} // O(n)

void destroySet(SET *sp) { //destroys the set and frees allocations
    assert(sp != NULL);
    int i;

    for (i = 0; i<sp->length; i++) {
        destroyList(sp->value[i]);
    }
    free(sp->value);
    free(sp);
} // O(n)

int numElements(SET *sp) { //returns number of elements
    assert(sp != NULL);
    return sp->count;
} // O(1)

void addElement(SET *sp, void *elt) { //adds element
    assert(sp != NULL && elt != NULL);
    int position;

    position = (sp->hash)(elt)%sp->length;
    if (findItem(sp->value[position], elt) == NULL) {
        addFirst(sp->value[position], elt);
        sp->count++;
    }
} // O(n)

void removeElement(SET *sp, void *elt) { //removes an element from set
    assert(sp != NULL && elt != NULL);
    int position;

    position = (sp->hash)(elt)%sp->length;
    if (findItem(sp->value[position], elt) != NULL) {
        removeItem(sp->value[position], elt);
        sp->count--;
    }
} // O(n)

void *findElement(SET *sp, void *elt) { //searches for element in set and returns it if present
    assert(sp != NULL && elt != NULL);
    int position;

    position = (sp->hash)(elt)%sp->length;
    return findItem(sp->value[position], elt);
} // O(n)

void *getElements(SET *sp) { //returns the set
    assert(sp != NULL || sp->count != 0);
    void **temp = malloc(sizeof(void*)*sp->count);
    int i, j, position;
    
    position = 0;
    for (i = 0; i<sp->length; i++) { //loops through everything 
        if (sp->value[i] != NULL) {
            void **items = getItems(sp->value[i]); 
            for (j = 0; j<numItems(sp->value[i]); j++) { //loops through list
                temp[position] = items[j]; //copies elements in the list
                position++; //adjusts position
            }
            free(items);
        }
    }
    return temp; //return the array
} // O(n)

