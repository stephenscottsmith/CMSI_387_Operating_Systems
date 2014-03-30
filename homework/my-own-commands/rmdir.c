/**
 * This program demonstrates invocation of the rmdir
 * system call (84 on 64-bit) using the syscall function.
 */
#include <linux/kernel.h> 
#include <linux/types.h>
#include <linux/unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int result = syscall(84, argv[1]);
    
	if (result == -1) {
		char *errorMessage = "Error: The operation could not be performed!\n";
		// Changed this syscall's first argument to 1 because I wrote this 
        // syscall for a 64-bit system, so it needs to use the 64-bit write
        // syscall which is 1 (not 4 like on 32-bit systems) 
        syscall(1, 2, errorMessage, strlen(errorMessage));
	}
}