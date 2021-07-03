/* Samuel Lim
 * Coen 12 Project 6
 * June 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set {
    void** value;
    int count;
    int length;
    char* flag;
    int (*compare)();
    unsigned (*hash)();
};

//big O notation is at end of each function

//intialize functions
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)());
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, void *elt);
void removeElement(SET *sp, void *elt);
void *findElement(SET *sp, void *elt);
void* getElements(SET *sp);
static int search(SET *sp, void *elt, bool* find);
static int partition(void** elts, int low, int high, int (*compare)());
static void quicksort(void** elts, int low, int high, int (*compare)());

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) { //creates set
    int i;
    SET *sp;
    
    sp = (SET*)malloc(sizeof(SET));
    assert(sp != NULL);
    sp->value = malloc(sizeof(void*)*maxElts);
    sp->count = 0;
    sp->length = maxElts;
    sp->flag = (char*)malloc(sizeof(char)*maxElts);
    sp->compare = compare;
    sp->hash = hash;
    
    for(i = 0; i < sp->length; i++) {
        sp->flag[i] = EMPTY; //makes every space empty
    }
    return sp;
} // O(n)

void destroySet(SET *sp) { //destroys set
    assert(sp != NULL);
    free(sp->value);
    free(sp->flag);
    free(sp);
    return;
} // O(n)

int numElements(SET *sp) { //number of elements in the set
    assert(sp != NULL);
    return sp->count;
} // O(n)

void addElement(SET *sp, void *elt) { //adds element to set
    assert((sp!=NULL || elt!=NULL) && (sp->count < sp->length));
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (!found) {
        sp->flag[position]= FILLED;
        sp->value[position]=strdup(elt);
        sp->count++;
    }
} // O(n)

void removeElement(SET *sp, void *elt) { //removes element from list
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (found) {
        free(sp->value[position]);
        sp->flag[position]= DELETED;
        sp->count--;
    }
} // O(n)

void *findElement(SET *sp, void *elt) { //returns position of the specified element
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (found) {
        return sp->value[position];
    }
    return NULL;
} // O(1)

void* getElements(SET *sp) { //returns array of elements in the set
    assert(sp!=NULL);
    void **elts;
    int i, j;
    
    elts = malloc(sizeof(void*)*(sp->count));
    for (i = 0, j = 0; i < sp->length; i++){
        if(sp->flag[i] == FILLED){
            elts[j++] = sp->value[i];
        }
    }
    quicksort(elts, 0, sp->count - 1, sp->compare);
    return elts;
} // O(n)

static int search(SET *sp, void *elt, bool* find) { //returns location of element
    assert(sp != NULL && elt != NULL);
    int counter, position, temp;
    
    counter = 0; //number of times searched
    position = (*sp->hash)(elt)%sp->length;
    temp = -1;
    
    while (counter < sp->length) {
        if(sp->flag[position] == EMPTY) {
            *find = false;
            return temp != -1 ? temp : position; //return index
        }
        else if (sp->flag[position] == DELETED) {
            counter++; //increase index by one then check again
            if (temp == -1) {
                temp = position;
            }
            position = (position + 1)%sp->length;
        }
        else {
            if ((*sp->compare)(sp->value[position], elt) == 0) { //compare function
                *find = true;
                return position;
            }
            else {
                position = (position + 1)%sp->length; //increase by one
                counter++;
            }
        }
    }
    *find = false;
    return temp;
} // O(n)

static int partition(void** elts, int low, int high, int (*compare)()) {
    void *wall = elts[high]; //wall is at the start
    int i, j;
    void *temp;

    j = low;
    for (i = low; i <= high-1; i++) { //for earch partition       
           if((*compare)(elts[i], wall) < 0) {
                 temp = elts[i]; //swapping
                 elts[i] = elts[j];
                 elts[j] = temp;
                 j++;
        }
    }
    temp = elts[j]; //swapping
    elts[j] = elts[high];
    elts[high] = temp;
    return j;
} // O(n)

static void quicksort(void** elts, int low, int high, int (*compare)()) {
    int index;
    
    if (low < high) { //if any other situation, no more sorting is needed
        index = partition(elts, low, high, compare);
        quicksort(elts, low, index - 1, compare); //below wall
        quicksort(elts, index + 1, high, compare); //above wall
    }
} // O(n^2)


