#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

int main() {
    FILE *myFile = NULL;
    
    myFile = fopen("diabetes_prediction_dataset.csv", "r");
    if (myFile == NULL) {
        printf("\nError de apertura de archivo.\n");
        exit(-1);
    } else {
        char buffer[MAXLINE];
        fgets(buffer, MAXLINE, myFile);

        while (fgets(buffer, MAXLINE, myFile)) {
            // If you need all the values in a row
            char *token = strtok(buffer, ",");
            while (token) { 
                printf("%s - ", token);

                token = strtok(NULL, ",");
            }
            printf("\n");
        }
        return 0;
    }
}