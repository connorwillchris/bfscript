all:
	gcc -o test bfscript.c jit/riscv/riscv_jit.c main.c

run:
	./test

clean:
	rm -rf test
