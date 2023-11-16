#include "shell.h"

/**
* _eputs - Prints an error message to standard error output.
* @string: Printed error message.
*
* Return: Nothing.
*/
void _eputs(char *string)
{
int index = 0;

if (!string)
return;
while (string[index] != '\0')
{
_eputchar(string[index]);
index++;
}
}

/**
* _eputchar - Writes a character to the standard error output.
* @p: The character.
*
* Return: On success, it returns 1.
* On error, -1 is returned, and errno is set.
*/
int _eputchar(char p)
{
static int index;
static char buffer[WRITE_BUFFER_SIZE];

if (p == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
{
write(2, buffer, index);
index = 0;
}
if (p != BUFFER_FLUSH)
buffer[index++] = p;
return (1);
}

/**
* _putfd - Function that writes a character to a specified file descriptor.
* @p: The character.
* @fd: The file descriptor.
*
* Return: On success, it returns 1.
* On error, -1 is returned, and errno is set.
*/
int _putfd(char p, int fd)
{
static int index;
static char buffer[WRITE_BUFFER_SIZE];

if (p == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
{
write(fd, buffer, index);
index = 0;
}
if (p != BUFFER_FLUSH)
buffer[index++] = p;
return (1);
}

/**
* _putsfd - Prints an input string to a specified file descriptor.
* @string: The string.
* @fd: The file descriptor.
*
* Return: The number of characters.
*/
int _putsfd(char *string, int fd)
{
int char_count = 0;

if (!string)
return (0);
while (*string)
{
char_count += _putfd(*string++, fd);
}
return (char_count);
}
