#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

ssize_t read_(int fd, void *buf, size_t count);
ssize_t write_(int fd, const void *buf, size_t count);
ssize_t read_until(int fd, void *buf, size_t count, char delimeter);
int spawn(const char * file, char * const argv []);

/*
typedef struct execargs_t
{
    char* command;
    char** argv;
} execargs_t;

execargs_t* execargs_new(char* command, char** argv);

int exec(execargs_t* args);
*/
