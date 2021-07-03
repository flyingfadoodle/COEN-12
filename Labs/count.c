/* Samuel Lim
   Coen 12 Lab 1
   April 4 2021
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[]) {
    int counter = 0;
    char words[MAX_WORD_LENGTH];
    FILE *file;
    
    if (argc != 2) { //test to see if file exists
        printf("Invalid file \n");
        return 0;
    }
    if ((file = fopen(argv[1], "r")) == NULL) { //if file exists, test to see if it can be opened
        printf("Unable to open %s, something went wrong \n", argv[1]);
    }
    else {
        while(fscanf(file, "%s", words) == 1) { //increases the counter by 1 for every succesful read
            counter++;
        }
    }
    printf("%d total words \n", counter);
}
