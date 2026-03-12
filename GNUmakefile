OBJDIR := obj
TOP    := .

ifeq ($(V),1)
override V =
else
override V = @
endif

# Toolchain (Native)
CC      := gcc
AS      := as
LD      := ld
OBJCOPY := objcopy
OBJDUMP := objdump
NM      := nm

# Flags
CFLAGS := -O1 -fno-builtin -I$(TOP) -MD -fno-omit-frame-pointer
CFLAGS += -std=gnu99 -static -Wall -g -m64
CFLAGS += -fno-stack-protector -fno-pic -mcmodel=kernel

LDFLAGS := -m elf_x86_64
KERN_CFLAGS := $(CFLAGS) -DJOS_KERNEL

GCC_LIB := $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)

# Include fragments
include lib/Makefrag
include kern/Makefrag

# Updated requirements list
LIMINE_REQS := boot/limine-bios.sys boot/limine-bios-cd.bin boot/limine-uefi-cd.bin boot/BOOTX64.EFI boot/limine
IMAGES      := $(OBJDIR)/kern/kernel.img

all: $(IMAGES)

# --- Updated Fetch Logic ---
$(LIMINE_REQS):
	@echo "+ fetching and building limine utility"
	$(V)mkdir -p boot
	$(V)rm -rf boot/limine_repo
	$(V)git clone https://github.com/limine-bootloader/limine.git --branch=v10.x-binary --depth=1 boot/limine_repo
	$(V)cp boot/limine_repo/limine-bios.sys boot/
	$(V)cp boot/limine_repo/limine-bios-cd.bin boot/
	$(V)cp boot/limine_repo/limine-uefi-cd.bin boot/
	$(V)cp boot/limine_repo/BOOTX64.EFI boot/
	$(V)$(CC) boot/limine_repo/limine.c -o boot/limine
	$(V)rm -rf boot/limine_repo

$(OBJDIR)/kern/kernel.img: $(OBJDIR)/kern/kernel $(LIMINE_REQS) limine.conf
	@echo "+ building ISO image"
	$(V)rm -rf $(OBJDIR)/iso_root
	$(V)mkdir -p $(OBJDIR)/iso_root/boot/limine
	$(V)mkdir -p $(OBJDIR)/iso_root/EFI/BOOT
	$(V)cp $(OBJDIR)/kern/kernel $(OBJDIR)/iso_root/boot/kernel
	$(V)cp boot/limine-bios.sys boot/limine-bios-cd.bin \
	       boot/limine-uefi-cd.bin $(OBJDIR)/iso_root/boot/limine/
	$(V)cp boot/BOOTX64.EFI $(OBJDIR)/iso_root/EFI/BOOT/
	$(V)cp limine.conf $(OBJDIR)/iso_root/boot/limine/limine.conf
	$(V)xorriso -as mkisofs -R -r -J \
		-b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		$(OBJDIR)/iso_root -o $@
	$(V)./boot/limine bios-install $@

qemu: $(IMAGES)
	qemu-system-x86_64 -drive file=$(IMAGES),format=raw -serial stdio

qemu-gdb: $(IMAGES)
	@echo "Starting QEMU for debugging..."
	$(V)qemu-system-x86_64 -m 512M -drive file=$(IMAGES),format=raw \
		-serial stdio \
		-d int,cpu_reset \
		-D qemu.log \
		-no-reboot -no-shutdown \
		-gdb tcp:localhost:1234 -S &
	@sleep 2
	@echo "Launching GDB..."
	$(V)gdb -x debug.gdb

clean:
	rm -rf $(OBJDIR)
	rm -f qemu.log

.PHONY: all clean qemu qemu-gdb
