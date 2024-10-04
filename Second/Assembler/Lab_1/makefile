all:
	gcc -c -g -ggdb -o main.o main.c
	nasm -f elf64 -F dwarf -g signed.asm -o signed.o
	nasm -f elf64 -F dwarf -g unsigned.asm -o unsigned.o
	gcc -m64 -o program signed.o unsigned.o main.o -g -ggdb -no-pie -z noexecstack
