CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -c
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T link.ld

OBJECTS = kernel_asm.o kernel.o

all: kernel.bin

kernel_asm.o: kernel.asm
	$(AS) $(ASFLAGS) kernel.asm -o kernel_asm.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) kernel.c -o kernel.o

kernel.bin: $(OBJECTS)
	$(LD) $(LDFLAGS) -o kernel.bin $(OBJECTS)

clean:
	rm -f *.o kernel.bin

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin -k en-us -device i8042 -vga std