#include "bufio.h"
#include <unistd.h>

const ssize_t BUF_SIZE = 4096;

int main() {
    struct buf_t* buf = buf_new(BUF_SIZE);
    do {
        ssize_t cnt = buf_fill(STDIN_FILENO, buf, buf_capacity(buf) - buf_size(buf));
        if (buf_size(buf) != buf_capacity(buf)) {
            buf_flush(STDOUT_FILENO, buf, buf_size(buf));
            buf_free(buf);
            if (cnt == -1){
                perror("failed on reading");
                return -1;
            }
            return 0;
        }
        if (buf_flush(STDOUT_FILENO, buf, buf_size(buf)) < 0)
            perror("failed on writing"); 
    } while(1);
}