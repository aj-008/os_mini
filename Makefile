C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

CC = /usr/bin/x86_64-elf-gcc
GDB = /usr/bin/gdb

CFLAGS = -g -m32 -ffreestanding


os-image.bin: boot/boot_sector.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -s -fda os-image.bin & ${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf32 -o $@

%.bin: %.asm
	nasm $< -f bin -o $@


clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
