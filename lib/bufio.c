#include "bufio.h"

struct buf_t {
    size_t size;
    size_t capacity;
    char *buf;
};

void abort_if_not_debug(){
    #ifdef DEBUG
        abort()
    #endif
}

struct buf_t *buf_new(size_t capacity) {
    char *buf = (char *)malloc(capacity * sizeof(char));
    struct buf_t *new_buf = malloc(sizeof(struct buf_t));
    if (buf ==NULL || new_buf == NULL) 
        return NULL;
    new_buf->size = 0;
    new_buf->capacity = capacity;
    new_buf->buf = buf;
    return new_buf;
}


void buf_free(struct buf_t *buf) {
    if (buf == NULL)
        abort_if_not_debug();
    free(buf->buf);
    free(buf);
}

ssize_t buf_fill(fd_t fd, struct buf_t *buf, size_t required) {
    if (buf_capacity(buf) - buf_size(buf) < required || buf == NULL)
        abort_if_not_debug();
    while (buf->size < required) {
        ssize_t cnt;
        if ((cnt = read(fd, buf->buf + buf->size, buf->capacity - buf->size)) == 0)
            break;
        if (cnt == -1) 
            return -1;
        buf->size += cnt;
    }
    return buf->size;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required) {
    if (buf == NULL)
        abort_if_not_debug();
    ssize_t res = buf->size;
    while (required >= 1) {
        ssize_t cnt;
        if ((cnt = write(fd, buf->buf, buf->size)) == -1)
            return -1;
        memmove(buf->buf, buf->buf + cnt, buf->size - cnt);
        required -= cnt;
        buf->size -= cnt;
        if (buf->size == 0) 
            break;
    }
    res -= buf->size;
    return res;
}

size_t buf_capacity(struct buf_t *buf) {
    if (buf == NULL) 
        abort_if_not_debug();
    return buf->capacity;
}

size_t buf_size(struct buf_t *buf) {
    if (buf == NULL)
        abort_if_not_debug();
    return buf->size;
}