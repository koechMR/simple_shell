#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
extern char **environ;
FILE *check_stream(int ac, char **av, FILE *stream);
void check_EOF(ssize_t readbytes, char *buf);
void trim_spaces(char *str);
void check_exit(char *buf);
void check_cd(char *cmd, char **tokensArray);
void cd_alone(int change_dir, size_t size, char *cd_buf);
void cd_with_arguments(int change_dir, size_t size, char *cd_buf);
void check_env(char *buf);
void check_bufcopy(char *bufcopy, char *buf);
void check_tokensArray(char **tokensArray, char *buf);
char *check_path_copy(char *path_copy);
void close_stream(int ac, FILE *stream);
void execute_cmd(char **tokensArray, char *actual_cmd);
void exit_check(char *cmd, char **tokensArray, int exit_status);
char *find_cmd(char *cmd);
void print_env(void);
size_t no_of_tokens(char *bufcopy, const char *delimeter);
char **tokenization(char *buf, char **tokensArray, const char *delimeter);
void process_cmd(char **tokensArray, char *program_name);
void free_tokensArray(char **tokensArray);
#endif
