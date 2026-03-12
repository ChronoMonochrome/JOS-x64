#ifndef JOS_INC_MEMLAYOUT_H
#define JOS_INC_MEMLAYOUT_H

#ifndef __ASSEMBLER__
#include <inc/types.h>
#include <inc/mmu.h>
#endif /* not __ASSEMBLER__ */

/*
 * Global descriptor numbers (64-bit)
 * In 64-bit mode, many fields in GDT are ignored, but selectors still exist.
 */
#define GD_KT     0x08     // kernel text
#define GD_KD     0x10     // kernel data
#define GD_UT     0x18     // user text
#define GD_UD     0x20     // user data
#define GD_TSS0   0x28     // TSS (Note: TSS is 16 bytes in 64-bit mode)

/*
 * Virtual memory map (64-bit):
 *
 * Start Addr                 Description
 * -----------------------------------------------------------------------
 * 0xffffffff80000000 (KERNBASE)  Remapped Physical Memory (up to 2GB)
 * 0xffffffff7f000000 (KSTACKTOP) Kernel Stacks
 * ...
 * 0x00007ffffffff000 (USTACKTOP) User Stack
 * 0x0000000000400000 (UTEXT)     User Program Start
 */

// All physical memory mapped at this high-half canonical address
// Limine and standard x86_64 kernels typically live here.
#define KERNBASE    0xffffffff80000000

#define IOPHYSMEM   0x0A0000
#define EXTPHYSMEM  0x100000

// Kernel stack.
#define KSTACKTOP   (KERNBASE - 0x1000000) // 16MB below KERNBASE
#define KSTKSIZE    (8*PGSIZE)             // size of a kernel stack
#define KSTKGAP     (8*PGSIZE)             // size of a kernel stack guard

// Top of user-accessible VM (Upper limit of lower canonical half)
#define UTOP        0x00007ffffffff000
#define USTACKTOP   UTOP
#define UXSTACKTOP  (USTACKTOP - PGSIZE)

// Where user programs generally begin (common for x86_64 ELF)
#define UTEXT       0x400000

// Top of user-accessible VM (Limit of the lower canonical half)
// On x86_64, this is usually 0x00007fffffffffff
#define ULIM        0x0000800000000000
#define UTOP        0x00007ffffffff000

// For compatibility with JOS code that checks boundaries
#define KERNBASE    0xffffffff80000000

#ifndef __ASSEMBLER__

/*
 * Page table entries are now 64 bits (8 bytes) in x86_64.
 */
typedef uint64_t pte_t;
typedef uint64_t pde_t;
typedef uint64_t pdpte_t;
typedef uint64_t pml4e_t;

#endif /* !__ASSEMBLER__ */
#endif /* !JOS_INC_MEMLAYOUT_H */
