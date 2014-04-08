/**
 * This program demonstrates invocation of the write and 
 * pause system calls using the syscall function.
 */
#include <linux/types.h>
#include <linux/unistd.h>
#include <string.h>

int main (int argc, char *argv[]) {
  syscall(351);
}
