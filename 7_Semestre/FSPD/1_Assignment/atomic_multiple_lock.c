#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getIntFromString(char **input, char **ptr) {
    int number = strtol(*input, ptr, 10);
    *input = *ptr;
    return number;

}

int main(){
    char input[30];
    while (fgets(input, sizeof(input), stdin)) {
        char *ptr = input;
        char *end;
        
        int tid = getIntFromString(&ptr, &end);
        int freeTime = getIntFromString(&ptr, &end);
        int criticalTime = getIntFromString(&ptr, &end);

        int resource[8];
        int nResource = 0;

        char *lastPtr = NULL;
    
        do
        {
            lastPtr = ptr;
            resource[nResource] = getIntFromString(&ptr, &end);
            printf("%p\n", end);
            nResource++;
        } while (end != lastPtr);
        
        while (end != lastPtr) {
        }

        printf("%d %d %d ", tid, freeTime, criticalTime);        

        int i;
        for(i = 0; i < nResource; i++) {
            printf("%d ", resource[i]);
        }

        printf("\n");
    }

    return 0;
}