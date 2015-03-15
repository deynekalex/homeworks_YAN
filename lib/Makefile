all: libhelpers.so

libhelpers.so: helpers.o read_until.o
	gcc -shared -o libhelpers.so helpers.o read_until.o

read_until.o: read_until.c
	gcc -c -std=c99 read_until.c

helpers.o: helpers.c
	gcc -c -std=c99 helpers.c
clean:
	rm -rf *.o libhelpers.so
