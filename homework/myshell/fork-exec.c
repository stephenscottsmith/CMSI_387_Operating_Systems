#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define MAX_COMMAND_LENGTH 256
#define MAX_NUMBER_ARGUMENTS 10
#define DELIM " "

// I need a function that modifies the input string by dividing it
// into an array of char*

// 1. Loop to ask for next command 
// (will need a terminating condition to exit loop)

// 2. Acknoledge the & and implement cd in a special way
// will happen before I fork

// 3. Super secret system call (351)


// Things I've learned/relearned about C
// 1. strlen returns the length of the 
//    string without the null character


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
        printf("Initial String Length: %d\n", strlen(command));

        command[strlen(command) - 1] = '\0';

        if (command[strlen(command) - 1] == '&') {
            printf("HI\n");
        }

        // parse command into individual arguments
        // site: http://www.lainoox.com/tokenize-string-c-strtok/
        char *arg = strtok(command, DELIM);
        int argIndex = 0;
        while (arg != NULL) {
            printf("HERE: %s\n", arg);
            arguments[argIndex] = arg;
            arg = strtok(NULL, DELIM);
            argIndex++;
        }

        // If there are arguments continue else skip this
        // iteration of the loop
        if ((strlen(command) - 1) != 0) {




        }


        // &
        // if ()        

        // cd
        // else if (strcmp(arguments[0], "cd") {
        //     chdir(arguments[1]);
        

        // Super secret system call
        // } else if {

        // }

	        


     //    /* Variable that will store the fork result. */
	    // pid_t pid;

	    // /* Perform the actual fork. */
	    // pid = fork();
	    // if (pid < 0) {
	    //     /* Error condition. */
	    //     fprintf(stderr, "Fork failed\n");
	    //     return -1;
	    // } else if (pid == 0) {
	    //     /* Child process. */
	    //     printf("Running...\n");
	    //     execlp(command, command, NULL);
	    // } else {
	    //     /* Parent process. */
	    //     int result;
	    //     wait(&result);
	    //     printf("All done; result = %d\n", result);
	    // }

	    // return 0;
    }
}