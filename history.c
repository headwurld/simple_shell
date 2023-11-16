#include "shell.h"

/**
* get_history_file - Retrieves the history file path.
* @info: Parameter.
*
* Return: Allocated string.
*/
char *get_history_file(info_t *info)
{
char *path, *home_dir;

home_dir = _getenv(info, "HOME=");
if (!home_dir)
return (NULL);
path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HISTORY_FILE) + 2));
if (!path)
{
	free(home_dir);
return (NULL);
}
path[0] = 0;
_strcpy(path, home_dir);
_strcat(path, "/");
_strcat(path, HISTORY_FILE);
free(home_dir);
return (path);
}

/**
* write_history_file - It creates a file.
* @info: Parameter.
*
* Return: 1 on success, -1 on failure.
*/
int write_history_file(info_t *info)
{
ssize_t fd;
char *fname = get_history_file(info);
list_t *node = NULL;

if (!fname)
return (-1);

fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(fname);

if (fd == -1)
return (-1);

for (node = info->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUFFER_FLUSH, fd);
close(fd);

return (1);
}

/**
* read_history_file - Reads history from a file.
* @info: Parameter.
* Return: The history count success, 0 otherwise.
*/
int read_history_file(info_t *info)
{
int p, last = 0, line_count = 0;
	ssize_t fd, readlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *fname = get_history_file(info);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	readlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (readlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (p = 0; p < fsize; p++)
		if (buffer[p] == '\n')
		{
			buffer[p] = 0;
			build_history_list(info, buffer + last, line_count++);
			last = p + 1;
		}
	if (last != p)
		build_history_list(info, buffer + last, line_count++);
	free(buffer);
	info->histcount = line_count;
	while (info->histcount-- >= MAX_HISTORY_SIZE)
		delete_node_at_index(&(info->history), 0);
	renumber_history_list(info);
	return (info->histcount);
}

/**
* build_history_list - Adds an entry.
* @info: Parameter structure.
* @buffer: The buffer.
* @line_count: The history line count.
*
* Return: 0.
*/
int build_history_list(info_t *info, char *buffer, int line_count)
{
list_t *node = NULL;

if (info->history)
node = info->history;

add_node_end(&node, buffer, line_count);

if (!info->history)
info->history = node;

return (0);
}

/**
* renumber_history_list - Renumbers the history list after changes.
* @info: Parameter struct.
*
* Return: The new history count.
*/
int renumber_history_list(info_t *info)
{
list_t *node = info->history;
int p = 0;

while (node)
{
node->num = p++;
node = node->next;
}

return (info->histcount = p);
}
