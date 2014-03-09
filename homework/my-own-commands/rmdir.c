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

    // JD: All fine, but for whatever reason I couldn't get the error
    //     message to turn up.  I tried a permissions problem, non-existent
    //     directory, etc....are you checking for the right value of result?
	if (result == -1) {
		char *errorMessage = "Error: The operation could not be performed!\n";
		syscall(4, 2, errorMessage, strlen(errorMessage));
	}
}