/**
 * This program demonstrates invocation of the getuid
 * system call (102 on 64-bit) using the syscall function.  Some
 * of its output is then displayed.
 */
#include <linux/kernel.h> 
#include <linux/types.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	uid_t userId = syscall(102);
	printf("%d\n", userId);
}