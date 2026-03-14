
## JOS-64: Porting to the Modern Era

This project is an experimental attempt to learn the "how and why" of operating systems by porting **JOS**—the classic MIT 6.828 teaching kernel - to a more modern environment.

----------

### 🚀 The Evolution

The original JOS was designed for a 32-bit environment, utilizing a custom two-stage bootloader and an entry sequence that handled the transition from Real Mode to Protected Mode. This project strips that away in favor of a 64-bit architecture.

#### Key Transitions:

-   **Architecture:** Shifted from **i386** to **x86-64 (Long Mode)**.
    
-   **Bootloader:** Replaced the legacy `boot/` block with **Limine**, a modern, lightweight bootloader that supports the Limine Boot Protocol.
    
-   **Memory Model:** Transitioned to a **High-Half Kernel** design. The kernel is linked and runs at `0xffffffff80000000`, utilizing the Higher Half Direct Map (HHDM) for physical memory access.
    
-   **Data Model:** Adopted the **LP64** data model (where `long` and `pointers` are 64-bit), requiring a refactor of core types and formatting libraries.
    

----------

### 🛠 Technical Highlights

-   **Modern Boot Protocol:** Using `limine.conf` to handle kernel loading, eliminating the need for complex assembly-based GDT switching in the first few sectors of the disk.
    
-   **64-bit Entry:** A rewritten `kern/entry.S` that establishes a 64-bit stack and jumps into the kernel C code in Long Mode immediately.
    
-   **HHDM Access:** Hardware-level drivers (like `console.c`) have been ported to use virtual offsets provided by the bootloader to access physical MMIO ranges (like the CGA buffer at `0xB8000`).
    

----------

### 📂 Project Structure

-   `inc/limine.h`: Limine protocol headers.
    
-   `kern/`: The heart of the kernel, containing the 64-bit entry point, console drivers, and the kernel monitor.
    
-   `lib/`: Minimalist C library ported for 64-bit pointer arithmetic and string manipulation.
    
-   `limine.conf`: Configuration for the bootloader, defining the kernel path and display settings.
    

----------

### 🚦 Getting Started

#### Prerequisites

-   `x86_64-elf-gcc` (or a native GCC with cross-compilation support)
    
-   `make`
    
-   `qemu-system-x86_64`
    
-   `xorriso` (for ISO creation)
    

#### Building and Running

1.  **Clone the repository:**
    
    Bash
    
    ```
    git clone https://github.com/your-repo/jos-64.git
    cd jos-64
    
    ```
    
2.  **Compile the kernel:**
    
    Bash
    
    ```
    make all
    
    ```
    
3.  **Run in QEMU:**
    
    Bash
    
    ```
    make qemu
    
    ```
    

