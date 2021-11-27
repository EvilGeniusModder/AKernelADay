#include <syscall.h>
#include <stddef.h>
#include <stdio.h>

/**
 * Invokes a system call using the following parameters.
 * @param num - The syscall identifer number.
 * @param a0 - Argument 0 specific to the syscall being invoked.
 * @param a1 - Argument 1 specific to the syscall being invoked.
 * @param a2 - Argument 2 specific to the syscall being invoked.
 * @param a3 - Argument 3 specific to the syscall being invoked.
 * @param a4 - Argument 4 specific to the syscall being invoked.
 * @param a5 - Argument 5 specific to the syscall being invoked.
 * @returns A return type specific to the syscall being invoked, sometimes errno is set othertimes neither errno nor the return value is set.
 */
extern unsigned long _syscall(int num, void* a0, void* a1, void* a2, void* a3, void* a4, void* a5);

/**
 * The exit syscall used to exit the program, also called by _start when main finished execution.
 * @param code - The code used to exit the program with.
 * @returns Nothing, we cannot return from this function as exit should be a last stop before program termination.
 */
extern __attribute__((noreturn)) void _exit(int code);

/**
 * Writes a buffer to a file.
 * @param fd - The file descriptor (a unique number specific to a file opened in this program).
 * @param buf - A buffer that contains the data to be written.
 * @param count - The number of characters in the buffer.
 * @returns The number of bytes actually written to the file, or -1 if the write fails.
 */
extern ssize_t write(unsigned int fd, const char* buf, size_t count);