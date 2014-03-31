/**
 * This program demonstrates invocation of the chmod
 * system call (90 on 64-bit) using the syscall function.  Some
 * of its output is then displayed.
 */
// JD: Again with the commented-out code.  Let it go, let it go...

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int permissions[3];
	int permNumber = atoi(argv[2]);
	int i = 2;
    while (permNumber > 0) {
		int digit = permNumber % 10;
		permNumber /= 10;	
		permissions[i] = digit;
		int temp = permissions[i];
		i--;					 
	}

	permissions[0] = permissions[0] << 6;
	permissions[1] = permissions[1] << 3;

	int result = syscall(90, argv[1], permissions[0] | permissions[1] | permissions[2]);

	if (result == -1) {
		char *errorMessage = "ERROR!";					
		syscall(4, 2, errorMessage, strlen(errorMessage));
	}
}