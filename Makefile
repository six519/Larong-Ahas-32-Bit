all: ahas.iso

clean:
	@rm -fv boot.o
	@rm -fv kernel.o
	@rm -fv vga.o
	@rm -fv bitmap.o
	@rm -fv utils.o
	@rm -fv ahas.o
	@rm -fv ahas.iso
	@rm -fv isodir/boot/ahas.bin

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

kernel.o: kernel.c
	gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

vga.o: vga.c
	gcc -m32 -c vga.c -o vga.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

bitmap.o: bitmap.c
	gcc -m32 -c bitmap.c -o bitmap.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

utils.o: utils.c
	gcc -m32 -c utils.c -o utils.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

ahas.o: ahas.c
	gcc -m32 -c ahas.c -o ahas.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

ahas.iso: boot.o kernel.o vga.o bitmap.o utils.o ahas.o
	ld -m elf_i386 -T link.ld kernel.o vga.o boot.o bitmap.o utils.o ahas.o -o ahas.bin -nostdlib
	mv ahas.bin isodir/boot/
	grub2-mkrescue -o ahas.iso isodir/