#include <stdio.h>
#include "App/App.h"


int main() {
/* The purpose of the while loop is to repeat the whole process depending on a user input (y/n) */

    int f=1;
    char c;
    while (f){

    // The main starting function
        appStart();

        // flushes input stream to clear the '\n'. (without this the new operation fails to take input from user and take '\n' instead
        fflush(stdin);

        printf("Process finished. Do you want to continue? (y/n): ");
        scanf("%c", &c);
        if(c=='y'){
            f=1;
            fflush(stdin);
        }else if(c=='n'){
            f=0;
        }
    }
    return 0;
}
