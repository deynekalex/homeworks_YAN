lib = -std=c99 -L../lib -Wl,-rpath=../lib -Wall -fPIC -I../lib
#commments

#-Wall - show all warnings
#-fPIc - If supported for the target machine, emit position-independent code, suitable for dynamic linking and avoiding any limit on the size of the global offset table.
#-I - Add the directory dir to the list of directories to be searched for header files. 
#-L - Search the library when linking.
all: cat

cat: cat.c 
	gcc $(lib) -o cat cat.c -lhelpers\

doublewords: doublewords.c
	gcc $(lib) -o doublewords doublewords.c -lhelpers\
	
clean:
	rm cat && rm doublewords
