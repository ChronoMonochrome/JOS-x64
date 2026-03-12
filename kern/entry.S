# kern/entry.S updated for 64-bit
.text
.code64
.globl _start
_start:
    # Set up the 64-bit stack
    movq $0, %rbp
    movq $(bootstacktop), %rsp

    # Call the C init function
    call i386_init

spin: jmp spin

.data
.p2align 12
.globl bootstack
bootstack:
    .space 32768
.p2align 4      # Ensure 16-byte alignment for the stack top
.globl bootstacktop
bootstacktop:
