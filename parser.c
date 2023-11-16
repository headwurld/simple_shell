#include "shell.h"

/**
* _iscmd - checks if a file is an executable command
* @info: the information struct
* @path: the path to the file
*
* Return: 1 if it's an executable, 0 otherwise
*/
int _iscmd(info_t *info, char *path)
{
struct stat file_stat;

(void)info;
if (!path || stat(path, &file_stat))
return (0);

if (file_stat.st_mode & S_IFREG)
return (1);

return (0);
}

/**
* _dupchars - creates a duplicate of characters within a range
* @pathstr: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: allocated pointer to a new buffer
*/
char *_dupchars(char *pathstr, int start, int stop)
{
static char buffer[1024];
int b = 0, k = 0;

for (k = 0, b = start; b < stop; b++)
{
if (pathstr[b] != ':')
buffer[k++] = pathstr[b];
}
buffer[k] = 0;
return (buffer);
}

/**
* find_exec_path - locates the full path of a command within the PATH string
* @info: the information struct
* @pathstr: the PATH string
* @cmd: the command to find
*
* Return: the full path of the command if found, or NULL if not
*/
char *find_exec_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, current_pos = 0;
char *path;

if (!pathstr)
return (NULL);

if ((_strlen(cmd) > 2) && starts_with_string(cmd, "./"))
{
if (_iscmd(info, cmd))
return (cmd);
}

while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = _dupchars(pathstr, current_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (_iscmd(info, path))
return (path);
if (!pathstr[i])
break;
current_pos = i;
}
i++;
}
return (NULL);
}
