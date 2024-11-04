#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *myFile = NULL;
    
    myFile = fopen("diabetes_prediction_dataset", "r");
    if (myFile == NULL) {
        printf("\nError de apertura de archivo.\n");
        exit(-1);
    } else {
        char buffer[80];
        while (fgets(buffer, 80, myFile)) {
            // If you need all the values in a row
            char *token = strtok(buffer, ",");
            while (token) { 
                // Just printing each integer here but handle as needed
                int n = atoi(token);
                printf("%d\n", n);

                token = strtok(NULL, ",");
            }
        }
        return 0;
    }
}