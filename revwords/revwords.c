#include "helpers.h"
#include <stdio.h>
#include <string.h>
#define BUFF_SIZE 8192

//Требуется реализовать утилиту revwords, читающую слова из stdin 
//и выводящую в stdout эти же слова развёрнутыми.
//Гарантируется, что каждое слово имеет длину не более 4096 байт.

const int BUFFER_SIZE = 8192;
const char DELIM = ' ';
char buffer[BUFF_SIZE];

void swap(int ch1, int ch2){
	char t = buffer[ch1];
	buffer[ch1] = buffer[ch2];
	buffer[ch2] = t;
}

void reverse(char* buffer, int n)
{
	for(int i=0;i<n/2;++i){
		swap(i, n - i - 1);
	}
}

int main()
{
    ssize_t result;
    size_t prev = 0;
    while((result = read_until(STDIN_FILENO, buffer+prev, BUFFER_SIZE-prev, DELIM))>0)
    {
        result+=prev;
        int prev_delim = 0;
        for (int i = 0; i < result; i++){
            if(buffer[i] == DELIM){
                reverse(buffer, i - prev_delim);//reverse until delimeter
                if(write_(STDOUT_FILENO, buffer + prev_delim, i - prev_delim + 1) == -1)//write reverse buffer + delimeter
                    perror("failed on writing");
                prev_delim = i + 1;
            }
        }
        memmove(buffer, buffer + prev_delim, result - prev_delim);//(dest, src, col) to copy
        prev = result - prev_delim;
    }
    reverse(buffer, prev);
    if(write_(STDOUT_FILENO, buffer, prev)==-1)
        perror("failed on writing");
    return 0;
}
