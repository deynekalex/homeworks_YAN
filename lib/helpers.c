#include "helpers.h"

//Требуется реализовать динамическую библиотеку, содержащую функции-хелперы read_ и write_, 
//делающие то же, что и read и write, но для буфера целиком (либо до EOF).
//Сигнатуры хелперов должны совпадать с сигнатурами оригинальных функций.

ssize_t read_(int fd, void *buf, size_t count){
	
	ssize_t real_counter;
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
    ssize_t real_counter;
	ssize_t col = count;
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

//Функция имеет ту же семантику, что и read_ из первого задания, с одним отличием: 
//она прекращает считывание из fd не только при заполнении буфера,
//но и при наличии символа delimiter в уже заполенной части буфера.

//в итоге ф-я записывает в fd блоки, последний блок содержит delimeter или является последним из источника.

ssize_t read_until(int fd, void *buf, size_t count, char delimiter)
{
    ssize_t actually_read;
    ssize_t overall = 0;
    while((actually_read = read(fd, buf, count)) > 0)
    {
        bool finded = false;
        for(int i = 0; i < actually_read; ++i){
            if(*((char*)buf + i) == delimiter){
                finded=true;
            }
        }
        overall+=actually_read;
        count-=actually_read;
        buf+=actually_read;
        if(finded) break;
    }
    if(actually_read==-1)
    {
        return -1;
    } else {
        return overall;
    }
}

//Функция должна запускать исполняемый файл file, выбираемый в соответствии с переменной окружения PATH, 
//с аргументами, задаваемыми в argv, дожидаться её завершения и возвращать её код возврата.

int spawn(const char * file, char * const argv []){
	pid_t pid;
	switch (pid = fork()){
		case -1:
			perror("failed on forking");
			exit(EXIT_FAILURE);
		break;
		case 0:;
			int fd = open("dev/null", O_WRONLY);
			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
			execvp(file, argv);
			close(fd);
			exit(EXIT_FAILURE);
		break;
		default:;
			int result;
			int res;
			res = waitpid(pid, &result, 0);
			if (res == -1){
				perror("failed on waiting");
				exit(EXIT_FAILURE);
			}
			return result;
		break;
	}
}
