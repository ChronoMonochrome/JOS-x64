# Connect to QEMU
target remote localhost:1234

# Load symbols from the kernel ELF file
file obj/kern/kernel

# Set the architecture to 64-bit
set arch i386:x86-64

# Break at the entry point defined in entry.S
break _start

# Break at the C entry point
break i386_init

# Continue to the first breakpoint
continue

# Useful display to see instructions as you step
display/5i $pc
