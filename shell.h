#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>

#define USE_STRTOK 0
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define MAX_HISTORY_SIZE 4096

extern char **environ;

typedef struct liststr
{
	int num;
	char *string;
	char *pref;
	char ctr;
	int index;
	char *str;
	struct liststr *next;
} list_t;


/**
* struct passinfo - Structure holding data for function parameters
* @arg: A string containing command arguments generated from getline
* @argv: An array of strings generated from arg
* @path: A string path for the current command
* @argc: Number of arguments
* @line_count: Error count
* @errnum: Error code for exit()
* @linecount_flag: Flag to determine if this line of input should be counted
* @fname: Program filename
* @env: Linked list local copy of the environment
* @environ: Custom modified copy of the environment from the linked list
* @history: The history node
* @alias: The alias node
* @env_changed: Flag to indicate if the environment was changed
* @status: The return status of the last executed command
* @cmd_buffer: Address of a pointer to cmd_buf
* @cmd_buffer_type: Type of command buffer (e.g., CMD_OR, CMD_AND, CMD_CHAIN)
* @readfd: The file descriptor for reading line input
* @histcount: History line number count
*/

typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int errnum;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buffer;
int cmd_buffer_type;
int readfd;
int histcount;
}
info_t;


#define INFO_INIT \
{\
NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0\
}

typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;



void fork_cmd(info_t *info);
void find_cmd(info_t *info);
int find_builtin(info_t *info);
int hsh(info_t *info, char **av);

int my_exit(info_t *info);
int my_cd(info_t *info);
int my_help(info_t *info);

void _eputs(char *string);
int _eputchar(char p);
int _putfd(char p, int fd);
int _putsfd(char *string, int fd);

list_t *add_node(list_t **head, const char *string, int num);
list_t *add_node_end(list_t **head, const char *string, int num);
size_t print_list_string(const list_t *first);
int delete_node_at_index(list_t **head, unsigned int index);
void _freelist(list_t **h_ptr);

int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *starts_with_string(const char *stack, const char *pin);
char *_strcat(char *destination, char *src);

int _myhistory(info_t *info);
int unset_alias(info_t *info, char *string);
int set_alias(info_t *info, char *string);
int print_alias(list_t *node);
int _myalias(info_t *info);

int _errrs2i(char *str);
void print_error(info_t *info, char *errstr);
int print_d(int data, int fd);
char *convert_num2base(long int digit, int b, int f);
void remove_comms(char *buffer);

size_t count_list(const list_t *head);
char **list_to_str_array(list_t *h);
size_t display_list(const list_t *head);
list_t *find_node_starts_with(list_t *node, char *pref, char ctr);
ssize_t get_node_index(list_t *h, list_t *node);

char *_strcpy(char *d, char *s);
char *_strdup(const char *s);
void _puts(char *s);
int _putchar(char p);

int _myenv(info_t *info);
char *_getenv(info_t *info, const char *var);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int initialize_enviro_list(info_t *info);

char *_strncpy(char *des, char *source, int name);
char *_strncat(char *s1, char *s2, int name);
char *_strchr(char *str, char a);

char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *v);
int _setenv(info_t *info, char *v, char *val);

ssize_t input_buffer(info_t *info, char **buffer, size_t *length);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buffer, size_t *s);
int _getline(info_t *info, char **p, size_t *len);
void Handler(__attribute__((unused))int signum);

char *get_history_file(info_t *info);
int write_history_file(info_t *info);
int read_history_file(info_t *info);
int build_history_list(info_t *info, char *buffer, int line_count);
int renumber_history_list(info_t *info);

void _clearinfo(info_t *info);
void _setinfo(info_t *info, char **av);
void free_info(info_t *info, int free_all);

int main(int argc, char **argv);

int freeAndNull(void **ptr);

int _iscmd(info_t *info, char *path);
char *_dupchars(char *pathstr, int start, int stop);
char *find_exec_path(info_t *info, char *pathstr, char *cmd);

char *fill_memory(char *dest, char byte, unsigned int size);
void free_string_array(char **ss);
void *_realloc(void *ptr, unsigned int p, unsigned int n);

int interactive_mode(info_t *info);
int is_delim(char p, char *d);
int _alphabet(int p);
int s2i(char *p);

char **strspt(char *str, char *d);
char **strspt2(char *str, char d);

int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int update_alias(info_t *info);
int varswap(info_t *info);
int replace_string(char **old, char *new);



#endif
