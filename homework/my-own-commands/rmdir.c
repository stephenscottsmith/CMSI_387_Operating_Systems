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
		syscall(4, 2, errorMessage, strlen(errorMessage));
	}
}