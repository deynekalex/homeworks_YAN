#include "read_until.h"
#include <stdbool.h>
ssize_t read_until(int fd, void *buf, size_t count, char delimeter){
	ssize_t real_counter = 0;
	ssize_t sum = 0;
	bool is_delimeted = 0;
	while((real_counter = read(fd, buf, count)) > 0){
		if (real_counter == -1){
			return -1;
		}
		for (int i = 0; i < real_counter; i++){
			if ((char*)*(buf+i) == delimeter){
				real_counter = i-1;
				is_delimeted = 1;
				break;
			}
		}
		if (!is_delimeted){
			sum += real_counter;
			count -= real_counter;
			buf += real_counter;
		}else{
			sum += real_counter;
			count = 0;
		}
	}
	return sum;
}
