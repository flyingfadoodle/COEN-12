

/* Samuel Lim
 *  *    Coen 12 Project 3
 *   *       April 2021
 *    *        */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

//intialize the functions
SET *createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);
static unsigned strhash(char *s);
static int search(SET *sp, char *elt, bool *found);

//big O notation is at the end of each function, I think it wasn't seen last lab and therefore got marked down
//all big O notation are for worse case
typedef struct set { //properties of the set
    char **value;
    int length;
    int count;
    char *flag;
} SET;


SET *createSet(int maxElts) { //creates a pointer to the new set
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    int i;
    sp->length = maxElts;
    sp->count = 0;
    sp->value = malloc(sizeof(char*)*maxElts);
    sp->flag = malloc(sizeof(char)*maxElts);
    assert(sp->value!=NULL && sp->flag!=NULL);
    for (i = 0; i<sp->length; i++) {
        sp->flag[i] = 0;
    }
    return sp;
} // O(n)

void destroySet(SET *sp) { //deallocates elements
    assert(sp!=NULL);
    int i;
    for (i=0; i<sp->length; i++){
        if (sp->flag[i]== 1)
            free(sp->value[i]);
    }
    free(sp->value);
    free(sp->flag);
    free(sp);
} // O(n)

int numElements(SET *sp) { //number of elements in the set
    return sp->count;
} // O(1)

void addElement(SET *sp, char *elt) { //adds element to the set
    assert(sp!=NULL || elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (!found) {
        sp->flag[position]= 1;
        sp->value[position]=strdup(elt);
        sp->count++;
    }
} // O(n)

void removeElement(SET *sp, char *elt) { //removes element from set
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (found) {
        free(sp->value[position]);
        sp->flag[position]= 2;
        sp->count--;
    }
} // O(n)

char *findElement(SET *sp, char *elt) { //tries to find a specific element in the set, returns NULL otherwise
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int position;
    
    position = search(sp, elt, &found);
    if (found) {
        return sp->value[position];
    }
    return NULL;
} // O(n)

char** getElements(SET *sp) { //copy of elements in the set
    assert(sp!=NULL);
    char **elts;
    int counter, i;
    
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

static unsigned strhash(char *s) { //hash function
    unsigned hash = 0;
    
    while (*s != '\0') {
        hash = 31 * hash + *s ++;
    }
    return hash;
} // O(1) 

static int search(SET *sp, char *elt, bool *found) { //searches for element in the set, then returns the position if found or where the element should be
    assert(sp!=NULL && elt!=NULL);
    int i, k, position, temp;
    
    k = 0;
    position = (strhash(elt)%sp->length);
    
    for (i = 0; i<sp->length; i++) { //different cases for found, deleted, not found
        temp = (position + i)%sp->length;
        
        if (sp->flag[temp] ==  EMPTY) {
            *found = false;
            if (k != 0) {
                return k;
            }
            else {
                return temp;
            }
        }
        
        if (sp->flag[temp] == FILLED) {
            if (strcmp(elt, sp->value[temp]) == 0) {
                *found = true;
                return temp;
            }
        }
        
        if (sp->flag[temp] == DELETED) {
            if (k == 0) {
                k = temp;
            }
        }
    }
    *found = false;
    return temp;
} // O(n)

