lib= -L../lib -Wl,-rpath=../lib -Wall -fPIC -I../lib -std=c99
#commments

#-Wall - show all warnings
#-fPIc - If supported for the target machine, emit position-independent code, suitable for dynamic linking and avoiding any limit on the size of the global offset table.
#-I - Add the directory dir to the list of directories to be searched for header files. 
#-L - Search the library when linking.
all: revwords

revwords: revwords.c
	gcc $(lib) -o revwords revwords.c -lhelpers

clean:
	rm revwords
