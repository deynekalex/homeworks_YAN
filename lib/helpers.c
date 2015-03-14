#include "helpers.h"
ssize_t read_(int fd, void *buf, size_t count){
	ssize_t real_counter = 0;
	ssize_t sum = 0;
	while((real_counter = read(fd, buf, count)) > 0){
		if (real_counter == -1){
			return -1;
		}
		sum += real_counter;
		count -= real_counter;
		buf += real_counter;
	}
	return sum;
}
ssize_t write_(int fd, const void *buf, size_t count){
	ssize_t col = count;
	ssize_t real_counter;
	while(col > 0){
		real_counter = write(fd, buf, count);
		if (real_counter == -1){
			return -1;
		}
		col -= real_counter;
		buf += real_counter;
	}
	return count;
}
