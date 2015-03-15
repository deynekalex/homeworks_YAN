lib= -L../lib -Wl,-rpath=../lib -Wall -fPIC -I../lib

all: cat

cat:
	gcc $(lib) -o cat cat.c -lhelpers

clean:
	rm cat
