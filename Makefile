OBJ_ASM = libmini64.o \
		  start.o \
		  libmini64-inclass.o
OBJ_C = libmini.o \
		libmini-inclass.o
TEST_FILES = alarm1.c alarm2.c alarm3.c jmp1.c

all: $(OBJ_ASM) $(OBJ_C)
	ld -shared -o libmini.so libmini64.o libmini.o libmini-inclass.o libmini64-inclass.o
	ar rcs libmini.a libmini64.o libmini.o libmini-inclass.o libmini64-inclass.o start.o

test: FORCE
	@echo "Compiling $(TEST_FILE)"
	gcc -c -g -Wall -fno-stack-protector -nostdlib -I. -I.. -DUSEMINI tests/$(TEST_FILE) -o test.o
	ld -m elf_x86_64 --dynamic-linker /lib64/ld-linux-x86-64.so.2 -o test test.o start.o -L. -L.. -lmini

FORCE: ;

%.o: %.asm
	yasm -f elf64 -DYASM -D__x86_64__ -DPIC $^ -o $@
%.o: %.c
	gcc -c -g -Wall -fno-stack-protector -fPIC -nostdlib $^

clean: 
	rm -f *.o *.so *.a
	rm -f test
