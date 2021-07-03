




/* Samuel Lim
 *    Coen 12 Project 5
 *       May 2021
 *        */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"
#include "pack.h"
#include <ctype.h>
#include <assert.h>

typedef struct node NODE;

static void readFile(char* fileName);
static NODE* makeNode(int count, NODE* left, NODE* right);
static int depth(NODE* np);
static int nodeCompare(NODE* np1, NODE* np2);

int ascii[257]; //index
NODE* nodes[257]; //will become the queue

int main(int argc, char *argv[]) {
    NODE *left, *right, *parent;
    PQ *pq; //queue
    int i, j;
    
    if (argc == 2) {
        puts("One or more files are missing \n");
        return 0;
    }
    else {
        readFile(argv[1]);
    }
    pq = createQueue(nodeCompare);
    
    for (i = 0; i < 256; i++) {
        if (ascii[i] > 0) { //every non-zero character is turned into a leaf in the queue
            nodes[i] = makeNode(ascii[i], NULL, NULL);
            addEntry(pq, nodes[i]);
        }
    }
    nodes[256] = makeNode(0, NULL, NULL); //make last spot 0 so the queue will never be empty
    addEntry(pq, nodes[256]);
    
    while (numEntries(pq) > 1) { //huffman tree
        left = removeEntry(pq); //smallest nodes are at the root
        right = removeEntry(pq);
        parent = makeNode(left->count + right->count, left, right);
        addEntry(pq, parent);
    }
    
    for (j = 0; j < 256; j++) { //loop through
        if (nodes[j] != NULL) {
            printf(isprint(j) ? "%c" : "%03o", j); //printing
            printf(": %d x %d bits = %d bits\n", ascii[j], depth(nodes[j]), ascii[j]*depth(nodes[j]));
        }
    }
    pack(argv[1], argv[2], nodes);
    destroyQueue(pq);
    return 0;
} // O(n)

static void readFile(char* fileName) { //reads the file
    FILE* fp = fopen(fileName, "r");
    int x;
    
    if (fp == NULL) { //makes sure file can be opened
        puts("File is unable to be opened \n");
        return;
    }
    x = getc(fp);
    
    while (x != EOF) {
        ascii[x]++; //+1 to frequency of character
        x = getc(fp);
    }
    fclose(fp);
    return;
} // O(n)

static NODE* makeNode(int value, NODE *left, NODE *right) { //makes node
    NODE* root = malloc(sizeof(NODE));
    assert(root != NULL);
    root->parent = NULL; //must determine parent later
    root->count = value; //number of occurences = value of node
    
    if (left != NULL){ //parent determination
        left->parent = root;
    }
    if(right != NULL){
        right->parent = root;
    }
    return root;
} // O(1)

static int depth(NODE* np) { //returns depth of given node
    assert(np != NULL);
    if (np->parent == NULL) {
        return 0;
    }
    return 1 + depth(np->parent);
} // O(n) worst case if it is the lowest node

static int nodeCompare(NODE* np1, NODE* np2) { //compares nodes
    assert(np1 != NULL && np2 != NULL);
    return (np1->count < np2->count) ? -1 : (np1->count > np2->count); //returns the larger node
} // O(1)

