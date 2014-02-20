/**
 * This program demonstrates invocation of the sysinfo
 * system call (116) using the syscall function.  Some
 * of its output is then displayed.
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/unistd.h>

#include <sys/types.h>
#include <sys/stat.h> 

// For convenience, we just use the stdio functions to display
// the output for this one.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int permissions[3];
	int permNumber = atoi(argv[1]);
	int i = 2;
    	while (permNumber > 0) {
		int digit = permNumber % 10;
		permNumber /= 10;	
		permissions[i] = digit;
		i--;					 
	}

	mode_t modes[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	int permBins[3] = {4, 2, 1};

	for (int k = 0; k < 3; k++) {
		int currentPerm = permissions[k];
		int modeIndex = 0;
		for (int j = 0; j < 3; j++) {
			currentPerm -= permBins[j];
			int result = 0;			
			if (currentPerm >= 0) {
				mode_t currentMode = modes[modeIndex];
				result = syscall(90, argv[2], currentMode);
				if (result == -1) {
					char *errorMessage = "ERROR!";					
					syscall(4, 2, errorMessage, strlen(errorMessage));
				}
			}
			modeIndex++;
		}
	}
}