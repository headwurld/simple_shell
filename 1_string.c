#include "shell.h"

/**
* _strcpy - Copy a string from source to destination.
* @d: The destination.
* @s: The source.
*
* Return: A pointer to the destination buffer.
*/
char *_strcpy(char *d, char *s)
{
int index = 0;

if (d == s || s == NULL)
return (d);

while (s[index])
{
d[index] = s[index];
index++;
}
d[index] = '\0';

return (d);
}

/**
* _strdup - Duplicate a string.
* @s: The string to duplicate.
*
* Return: A pointer to the duplicated string or NULL on failure.
*/
char *_strdup(const char *s)
{
int length = 0;
char *dup;

if (s == NULL)
return (NULL);

while (*s++)
length++;

dup = malloc(sizeof(char) * (length + 1));
if (!dup)
return (NULL);

for (length++; length--;)
dup[length] = *--s;
free(dup);
return (dup);
}

/**
* _puts - Prints an input string to standard output.
* @s: The string.
*
* Return: Nothing.
*/
void _puts(char *s)
{
int index = 0;

if (!s)
return;

while (s[index] != '\0')
{
_putchar(s[index]);
index++;
}
}

/**
* _putchar - Write a character to the standard output.
* @p: The character to print.
*
* Return: On success, it returns 1. On error, -1 is returned,
* and errno is set appropriately.
*/
int _putchar(char p)
{
static int bufIndex;
static char buffer[WRITE_BUFFER_SIZE];

if (p == BUFFER_FLUSH || bufIndex >= WRITE_BUFFER_SIZE)
{
write(1, buffer, bufIndex);
bufIndex = 0;
}

if (p != BUFFER_FLUSH)
buffer[bufIndex++] = p;

return (1);
}
