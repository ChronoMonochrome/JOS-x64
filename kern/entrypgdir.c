#include <inc/mmu.h>
#include <inc/memlayout.h>
#include <inc/x86.h>

// Forward declaration so entry_pgdir knows this exists
extern pte_t entry_pgtable[NPTENTRIES];

// The entry.S page directory maps the first 4MB of physical memory
__attribute__((__aligned__(PGSIZE)))
pde_t entry_pgdir[NPDENTRIES] = {
	// Map VA's [0, 4MB) to PA's [0, 4MB)
	[0] = ((uintptr_t)entry_pgtable - KERNBASE) + PTE_P,

	// Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
	[KERNBASE >> PDXSHIFT] = ((uintptr_t)entry_pgtable - KERNBASE) + PTE_P + PTE_W
};

// Use a unique name for our local generation macro to avoid mmu.h conflicts
#define MK_PTE(i) [(i)] = ((i) << PGSHIFT) | PTE_P | PTE_W

__attribute__((__aligned__(PGSIZE)))
pte_t entry_pgtable[NPTENTRIES] = {
	#define E10(i) \
	MK_PTE(i+0), MK_PTE(i+1), MK_PTE(i+2), MK_PTE(i+3), MK_PTE(i+4), \
	MK_PTE(i+5), MK_PTE(i+6), MK_PTE(i+7), MK_PTE(i+8), MK_PTE(i+9)

	#define E100(i) \
	E10(i+0),  E10(i+10), E10(i+20), E10(i+30), E10(i+40), \
	E10(i+50), E10(i+60), E10(i+70), E10(i+80), E10(i+90)

	// Fill 1000 entries (0-999)
	E100(0),   E100(100), E100(200), E100(300), E100(400),
	E100(500), E100(600), E100(700), E100(800), E100(900),

	// Fill the last 24 entries to reach 1024
	E10(1000), E10(1010),
	MK_PTE(1020), MK_PTE(1021), MK_PTE(1022), MK_PTE(1023)
};
