#include "shell.h"

/**
* hsh - The central loop of the shell
* @info: the pointer to the information structure for parameter & return
* @av: the argument vector received from main() function
*
* Return: 0 on success, 1 on error, or an appropriate error code
*/
int hsh(info_t *info, char **av)
{
ssize_t p = 0;
int builtin_result = 0;

while (p != -1 && builtin_result != -2)
{
_clearinfo(info);
if (interactive_mode(info))
_puts("$ ");
_eputchar(BUFFER_FLUSH);
p = get_input(info);
if (p != -1)
{
_setinfo(info, av);
builtin_result = find_builtin(info);
if (builtin_result == -1)
find_cmd(info);
}
else if (interactive_mode(info))
_putchar('\n');
free_info(info, 0);
}
write_history_file(info);
free_info(info, 1);
if (!interactive_mode(info) && info->status)
exit(info->status);
if (builtin_result == -2)
{
if (info->errnum == -1)
exit(info->status);
exit(info->errnum);
}
return (builtin_result);
}

/**
* find_builtin - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
*          0 successfully,
*          1 not successful,
*         -2 exit()
*/
int find_builtin(info_t *info)
{
int p, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", my_exit},
{"env", _myenv},
{"help", my_help},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", my_cd},
{"alias", _myalias},
{NULL, NULL}
};

for (p = 0; builtintbl[p].type; p++)
if (_strcmp(info->argv[0], builtintbl[p].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[p].func(info);
break;
}
return (built_in_ret);
}

/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(info_t *info)
{
char *path = NULL;
int p, k;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (p = 0, k = 0; info->arg[p]; p++)
if (!is_delim(info->arg[p], " \t\n"))
k++;
if (!k)
return;

path = find_exec_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((interactive_mode(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && _iscmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* fork_cmd - forks and executes a command.
* @info: the parameter and return info struct.
*
* Return: void
*/
void fork_cmd(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("fork_cmd - Forking failed");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
