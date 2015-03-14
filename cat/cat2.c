#include "helpers.h"
#include <stdio.h>

const size_t BUFF_SIZE  = 1024;

int main(){
	char buffer[BUFF_SIZE];
	ssize_t res;
	while((res = read_(STDIN_FILENO, buffer, BUFF_SIZE)) > 0){
		if (res == -1)
			perror("failed on reading");
		if (write_(STDOUT_FILENO, buffer, res) < 0)
			perror("failed on writing");
	}
	return 0;
}