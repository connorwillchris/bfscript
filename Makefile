all:
	gcc -o test bfscript.c main.c 

run:
	./test

clean:
	rm -rf test
