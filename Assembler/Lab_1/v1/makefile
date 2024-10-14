# makefile

all:
	gcc -c -g -ggdb -o main.o main.c
	nasm -f elf64 -F dwarf -g calc.asm -o calc.o
	gcc -m64 -o prog calc.o main.o -g -ggdb -no-pie -z noexecstack	
clean:
	rm -f *.o prog
