#include "shell.h"

/**
* my_exit - Exit the shell
* @info: Structure with possible arguments.
*
* Return: Exits with a given exit status (0) if info->argv[0] != "exit".
*/
int my_exit(info_t *info)
{
int exit_status;

if (info->argv[1])
{
exit_status = _errrs2i(info->argv[1]);
if (exit_status == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->errnum = _errrs2i(info->argv[1]);
return (-2);
}
info->errnum = -1;
return (-2);
}

/**
* my_cd - Changes the current directory of the process
* @info: Structure with possible arguments.
*
* Return: Always 0
*/
int my_cd(info_t *info)
{
char *current_dir, *dir, buffer[1024];
int chdir_result;

current_dir = getcwd(buffer, 1024);
if (!current_dir)
_puts("TODO: Handle getcwd failure message here\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_result = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_result = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(current_dir);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD="));
_putchar('\n');
chdir_result = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_result = chdir(info->argv[1]);
if (chdir_result == -1)
{
print_error(info, "Can't change directory to ");
_eputs(info->argv[1]);
_eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* my_help - Provides help information for the shell.
* @info: Structure with possible arguments.
*
* Return: Always 0
*/
int my_help(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("Help command works. Function not yet implemented\n");
if (0)
_puts(*arg_array);
return (0);
}
