.globl _syscall
_syscall: # This is the x86 system call calling convention.
    movq %rdi, %rax # Call ID (specific to the type of call being made).
    movq %rsi, %rdi # ARG 0
    movq %rdx, %rsi # ARG 1
    movq %rcx, %rdx # ARG 2
    movq %r8, %r10 # ARG3
    movq %r9, %r8 # ARG4
    movq 8(%rsp), %r9 # ARG5
    syscall # Invoke the system call.
    ret # Return from this helper function.
