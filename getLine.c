#include "shell.h"

/**
* input_buffer - Buffers chained commands.
* @info: Structure containing potential arguments.
* @buffer: Address of the buffer.
* @length: Address of length variable.
*
* Return: Number of bytes read.
*/
ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
ssize_t c = 0;
size_t len_p = 0;

if (!*length)
{
/*freeAndNull((void **)info->cmd_buf);*/
free(*buffer);
*buffer = NULL;
signal(SIGINT, Handler);
#if USE_GETLINE
c = getline(buffer, &len_p, stdin);
#else
c = _getline(info, buffer, &len_p);
#endif
if (c > 0)
{
if ((*buffer)[c - 1] == '\n')
{
(*buffer)[c - 1] = '\0'; /* Remove trailing newline */
c--;
}
info->linecount_flag = 1;
remove_comms(*buffer);
build_history_list(info, *buffer, info->histcount++);

{
*length = c;
info->cmd_buffer = buffer;
}
}
}
return (c);
}

/**
* get_input - Retrieves a line without the newline character.
* @info: Structure with potential arguments.
*
* Return: Number of bytes to be read.
*/
ssize_t get_input(info_t *info)
{
static char *buffer; /* The ';' command chain buffer */
static size_t i, k, length;
ssize_t c = 0;
char **buffer_p = &(info->arg), *p;

_putchar(BUFFER_FLUSH);
c = input_buffer(info, &buffer, &length);
if (c == -1) /* EOF */
return (-1);
if (length)
{
k = i;
p = buffer + i;

check_chain(info, buffer, &k, i, length);
while (k < length) /* Iterate to semicolon or end */
{
if (is_chain(info, buffer, &k))
break;
k++;
}

i = k + 1; /* Increment past the nullified semicolon */
if (i >= length) /* Reached the end of the buffer? */
{
i = length = 0; /* Reset position and length */
info->cmd_buffer_type = COMMAND_NORMAL;
}

*buffer_p = p; /* Pass back a pointer to the current command position */
return (_strlen(p)); /* Return the length of the current command */
}
/* Not a chain, pass back the buffer from custom_getline() */
*buffer_p = buffer;
return (c); /* Return the length of the buffer from custom_getline() */
}

/**
* read_buf - Reads a buffer.
* @info: Structure containing potential arguments.
* @buffer: Buffer.
* @s: Size.
*
* Return: c
*/
ssize_t read_buf(info_t *info, char *buffer, size_t *s)
{
ssize_t c = 0;

if (*s)
return (0);
c = read(info->readfd, buffer, READ_BUFFER_SIZE);
if (c >= 0)
*s = c;
return (c);
}

/**
* _getline - Gets the next line of input from STDIN.
* @info: Structure containing potential arguments.
* @p: Address of pointer to buffer, preallocated or NULL.
* @len: Size of preallocated ptr buffer if not NULL.
*
* Return: r
*/
int _getline(info_t *info, char **p, size_t *len)
{
static char buf[READ_BUFFER_SIZE];
static size_t i, l;
size_t k;
ssize_t d = 0, r = 0;
char *c = NULL, *new_c = NULL, *a;

c = *p;
if (c && len)
r = *len;
if (i == l)
i = l = 0;

d = read_buf(info, buf, &l);
if (d == -1 || (d == 0 && l == 0))
return (-1);

a = _strchr(buf + i, '\n');
k = a ? 1 + (unsigned int)(a - buf) : l;
new_c = _realloc(c, r, r ? r + k : k + 1);
if (!new_c) /* MALLOC FAILURE! */
return (c ? free(c), -1 : -1);

if (r)
_strncat(new_c, buf + i, k - i);
else
_strncpy(new_c, buf + i, k - i + 1);

r += k - i;
i = k;
c = new_c;

if (len)
*len = r;
*p = c;
return (r);
}

/**
* Handler - Blocks the Ctrl-C signal.
* @signum: The signal number.
*
* Return: void
*/
void Handler(__attribute__((unused))int signum)
{
_puts("\n");
_puts("$ ");
_putchar(BUFFER_FLUSH);
}
