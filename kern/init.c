#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/assert.h>
#include <inc/types.h>
#include <kern/monitor.h>
#include <kern/console.h>
#include <inc/limine.h>

// Entry point for Limine
void
i386_init(void)
{
	extern char edata[], end[];

	// Clear BSS using uintptr_t for 64-bit safety
	memset(edata, 0, (uintptr_t)end - (uintptr_t)edata);

	cons_init();
	cprintf("JOS is booting via Limine 10.x!\n");

	while (1)
		monitor(NULL);
}

const char *panicstr;

void
_panic(const char *file, int line, const char *fmt,...)
{
	va_list ap;

	if (panicstr)
		goto dead;
	panicstr = fmt;

	asm volatile("cli; cld");

	va_start(ap, fmt);
	cprintf("kernel panic at %s:%d: ", file, line);
	vcprintf(fmt, ap);
	cprintf("\n");
	va_end(ap);

	dead:
	while (1)
		monitor(NULL);
}
