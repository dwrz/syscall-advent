cat: cat.c
	gcc cat.c -o cat

run: ./cat
	./cat cat.c makefile

strace: ./cat
	strace ./cat cat.c makefile > /dev/null
