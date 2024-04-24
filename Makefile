all:
	gcc -o test bfscript.c jit/riscv/riscv_jit.c jit/riscv/riscv.c main.c

run:
	./test

clean:
	rm -rf test
