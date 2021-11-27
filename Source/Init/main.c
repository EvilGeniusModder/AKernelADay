#include "Syscalls.h"

/**
 * The exit syscall used to exit the program, also called by _start when main finished execution.
 * @param code - The code used to exit the program with.
 * @returns Nothing, we cannot return from this function as exit should be a last stop before program termination.
 */
extern __attribute__((noreturn)) void _exit(int code) {
    while(1) _syscall(SYS_exit,(void*)(long)code,0,0,0,0,0);
}

/**
 * Writes a buffer to a file.
 * @param fd - The file descriptor (a unique number specific to a file opened in this program).
 * @param buf - A buffer that contains the data to be written.
 * @param count - The number of characters in the buffer.
 * @returns The number of bytes actually written to the file, or -1 if the write fails.
 */
extern ssize_t write(unsigned int fd, const char* buf, size_t count) {
    return _syscall(SYS_write, (void*)(long)fd, (void*)(long)buf, (void*)(long)count, 0, 0, 0);
}

/**
 * The standard "main" most people are familiar with when using C (or C++). We dont use the argc or argv parameters to begin with since this program is invoked by the kernel there should be nothing in argv.
 * @param argc - The number of arguments passed in at argv.
 * @param argv - A string array containing user defined arguments.
 * @returns An errno or 0 if successfull execution.
 */
int main(/*int argc, char** argv*/){

    write(1, "+=======[ Generic OS ]=======+\n", 32);
    write(1, "Hello World\n", 13);

    //We enter into an infinite loop since the kernel called us and we cant pass back control to the kernel cause it might crash.
    while(1) {};
    return 0;
}

