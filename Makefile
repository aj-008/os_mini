# Toolchain
CC := i386-elf-gcc
LD := i386-elf-ld
AS := nasm
OBJCOPY := objcopy
GDB := gdb
GRUB_MKRESCUE := grub-mkrescue
QEMU := qemu-system-i386

# Flags
CFLAGS := -m32 -ffreestanding -Wall -Wextra -O0 -g
ASMFLAGS := -f elf32
LDFLAGS := -m elf_i386 -T linker.ld

# Kernel ELF
KERNEL := kernel.elf
ISO_DIR := iso/boot
ISO_IMG := os.iso

# Sources
ASM_SRCS := mbh.asm cpu/interrupt.asm paging/enable_paging.asm
C_SRCS := $(wildcard */*.c) $(wildcard *.c)
C_SRCS := $(filter-out boot/%,$(C_SRCS))  # optional

# Objects (same directory as sources)
OBJ := $(patsubst %.c,%.o,$(C_SRCS)) $(patsubst %.asm,%.o,$(ASM_SRCS))
MBH_OBJ := mbh.o

.PHONY: all clean iso run qemu-gdb gdb

all: $(KERNEL)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble ASM files
%.o: %.asm
	$(AS) $(ASMFLAGS) $< -o $@

# Link kernel (mbh.o first)
$(KERNEL): $(MBH_OBJ) $(filter-out $(MBH_OBJ),$(OBJ)) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(MBH_OBJ) $(filter-out $(MBH_OBJ),$(OBJ))
	$(OBJCOPY) -O elf32-i386 $@ $@

# Prepare ISO
iso: $(KERNEL)
	@mkdir -p $(ISO_DIR)
	cp $(KERNEL) $(ISO_DIR)/kernel.elf
	$(GRUB_MKRESCUE) -o $(ISO_IMG) iso

# Run QEMU
run: iso
	$(QEMU) -cdrom $(ISO_IMG) -m 512 -serial stdio

# QEMU with GDB
qemu-gdb: iso
	$(QEMU) -cdrom $(ISO_IMG) -m 512 -gdb tcp::1234 -S -no-reboot -serial stdio

# Connect GDB
gdb: $(KERNEL)
	$(GDB) -ex "file $(KERNEL)" -ex "set architecture i386" -ex "target remote localhost:1234"

# Clean
clean:
	rm -f $(OBJ) $(KERNEL) $(ISO_IMG)

