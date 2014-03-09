/**
 * This program demonstrates invocation of the chmod
 * system call (90 on 64-bit) using the syscall function.  Some
 * of its output is then displayed.
 */
// JD: Again with the commented-out code.  Let it go, let it go...

// #include <linux/kernel.h>
// #include <linux/types.h>
// #include <linux/unistd.h>
// #include <types.h>
// #include <stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int permissions[3];
	int permNumber = atoi(argv[1]);
	int i = 2;
    while (permNumber > 0) {
		int digit = permNumber % 10;
		permNumber /= 10;	
		permissions[i] = digit;
		int temp = permissions[i];
		printf("%d", temp);
		i--;					 
	}

	permissions[0] = permissions[0] << 6;
	printf("%o", permissions[0]);

    // JD: Idina Menzel is giving you the stinkeye.
    //     Oh wait---*you actually forgot to reinstate the system call*!!!
    //     Achievement revoked  O_o

	// mode_t modes[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	// int permBins[3] = {4, 2, 1};
	// int modeIndex = 0;
	// for (int k = 0; k < 3; k++) {
	// 	int currentPerm = permissions[k];
		
	// 	for (int j = 0; j < 3; j++) {
			
	// 		printf("Current Perm: %d\n", currentPerm);
	// 		int result = 0;			
	// 		if (currentPerm >= 0) {
	// 			printf("HERE\n");				
	// 			mode_t currentMode = modes[modeIndex];
	// 			printf("Mode Index: %d\n", modeIndex);
	// 			result = syscall(90, argv[2], currentMode);
	// 			printf("Result: %d\n", result);
	// 			if (result == -1) {
	// 				char *errorMessage = "ERROR!";					
	// 				syscall(4, 2, errorMessage, strlen(errorMessage));
	// 			}
	// 		}
	// 		currentPerm -= permBins[j];			
	// 		modeIndex++;
	// 	}
	// }
}