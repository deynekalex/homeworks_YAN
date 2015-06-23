C_FLAGS= -L../lib -Wl,-rpath=../lib -Wall -fPIC -std=c99 -g -I../lib

all: filter

filter: filter.c
	gcc $(C_FLAGS) -o filter filter.c -lhelpers

clean:
	rm -f filter
	rm -f test 
