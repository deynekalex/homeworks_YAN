	#include "helpers.h" 
#include <string.h>
#include <stdio.h>

const int BUFFER_SIZE = 8192; 
const char DELIM = '\n';
const int ARG_SIZE = 256;
const int LAST_ARG_SIZE = 8192;

int spawn2(const char * file, char * const argv []){
	pid_t pid;
	switch (pid = fork()){
		case -1:
			perror("failed on forking");
			exit(EXIT_FAILURE);
		break;
		case 0:;
			int fd = open("/dev/null", O_WRONLY);
			if (fd == -1)
				perror("open");
			if (dup2(fd, STDERR_FILENO))
				perror("dup2");
			if (dup2(fd, STDOUT_FILENO))
				perror("dup2");
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
			return WEXITSTATUS(result);
		break;
	}
}

int main(int argc, char* argv[])
{
	char* args[3];
	char buf[BUFFER_SIZE];
	args[0] = malloc(BUFFER_SIZE);
	ssize_t res = read_until(STDIN_FILENO, args[0], BUFFER_SIZE, '\n');
	for (int i = 0; i < res; i++){
		if (args[0][i] == '\n'){
			args[0][i] = '\0';
		}
	}
	
	args[2] = NULL;
    for (int i = 1; i < argc; i++){
    	args[1] = argv[i];
    	// for (int j = 0; j < 3; j++){
    	// 	printf("\n");
    	// 	printf("%s\n", args[j]);
    	// 	printf("\n");
    	// }
        ssize_t res = spawn2(args[0], args);
        if (res % 256 == 0){
      		sprintf(buf, "good at arg = %d\n", i);
        	write(STDOUT_FILENO, buf, strlen(buf));

        }else{
        	sprintf(buf, "bad at arg = %d\n", i);
        	write(STDOUT_FILENO, buf, strlen(buf));        
        }
    }
    return 0;
}