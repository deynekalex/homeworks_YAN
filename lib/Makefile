all: libhelpers.so

libhelpers.so: helpers.o
	gcc -shared -o libhelpers.so helpers.o

helpers.o: helpers.c
	gcc -c helpers.c
clean:
	rm -rf *.o libhelpers.so
