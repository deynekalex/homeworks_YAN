#include <helpers.h>
#include <stdio.h>

//В первом задании необходимо реализовать примитивный вариант утилиты cat, 
//копирующий символы из stdin на stdout.

const size_t BUFF_SIZE  = 4096;

int main(){
	char buffer[BUFF_SIZE];
	ssize_t res;
	while((res = read_(STDIN_FILENO, buffer, BUFF_SIZE)) > 0){
		if (res == -1){
			perror("failed on reading");
			return -1;
		}
		if (write_(STDOUT_FILENO, buffer, res) < 0){
			perror("failed on writing");
			return -1;
		}
	}
	return 0;
}
