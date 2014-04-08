#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define MAX_COMMAND_LENGTH 256
#define MAX_NUMBER_ARGUMENTS 10
#define DELIM " \n"

// Things I've learned/relearned about C
// 1. strlen returns the length of the 
//    string without the null character
// 2. fgets has the characters of the input
//    string with a \n at the end, needed to replace
//    with a \0

int main(void) {
    /* Command and it's argument array */
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_NUMBER_ARGUMENTS];

    /* Visual Shell */
    char *newCommand = "--> ";

    while (!feof(stdin)) {
        // Display prompt and get command input
        fputs(newCommand, stdout);
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';
        int background = 0;
            

        if (command[strlen(command) - 1] == '&') {
                background = 1;
                // printf("backgrounding");
        }

        while (command[strlen(command) - 1] == ' ') {
            command[strlen(command) - 1] = '\0';
        }
        // parse command into individual arguments
        // site: http://www.lainoox.com/tokenize-string-c-strtok/
        char *delim = " \n";
        char *arg = strtok(command, delim);
        int argIndex = 0;
        while (arg != NULL) {
            arguments[argIndex] = arg;
            arg = strtok(NULL, delim);
            argIndex++;
        }
        arguments[argIndex] = NULL;
        
        // If there are arguments continue else skip this
        // iteration of the loop
        if ((strlen(command) - 1) != 0) {

            if (strcmp("cd", arguments[0]) == 0) {
                chdir(arguments[1]);
            } else if (strcmp("secret-system-call", arguments[0]) == 0) {
                int result = syscall(351);
            } else if (strcmp("quit", arguments[0]) == 0) {
                return 1;
            } else {
                pid_t pid;

                /* Perform the actual fork. */
                pid = fork();
                if (pid < 0) {
                    /* Error condition. */
                    return -1;
                } else if (pid == 0) {
                    /* Child process. */
                    execvp(arguments[0], arguments);
                } else {
                    /* Parent process. */
                    int result;
                    if (!background) {
                        wait(&result);
                    }
                }
            }
        }
    }

    return 0;
}