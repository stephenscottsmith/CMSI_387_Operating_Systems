#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>


#define MAX_COMMAND_LENGTH 256
#define MAX_NUMBER_ARGUMENTS 10

int main(void) {
    /* Command and it's argument array */
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_NUMBER_ARGUMENTS];

    /* Visual Shell */
    char *newline = "--> ";

    while (!feof(stdin)) {
        fputs(newline, stdout);
        fgets(command, sizeof(command), stdin);
        fputs(command, stdout);



    }
}