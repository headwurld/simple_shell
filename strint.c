#include "shell.h"

/**
* interactive_mode - checks whether the shell operates in an interactive mode.
* @info: a pointer to the info_t structure
*
* Return: 1 if the shell is running interactively, 0 if it's not.
*/
int interactive_mode(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim - checks if a character is a delimiter
* @p: the character to check
* @d: a string containing delimiters
* Return: 1 if the character is a delimiter, 0 otherwise
*/
int is_delim(char p, char *d)
{
while (*d)
if (*d++ == p)
return (1);
return (0);
}

/**
* _alphabet - checks if a character is alphabetic
* @p: the character to check
* Return: 1 if the character is alphabetic, 0 otherwise
*/
int _alphabet(int p)
{
if ((p >= 'a' && p <= 'z') || (p >= 'A' && p <= 'Z'))
return (1);
else
return (0);
}

/**
* s2i - a function that takes a string as input and converts into an integer.
* @p: the particular string to be converted.
* Return: 0 if the string contains no numeric values.
*/
int s2i(char *p)
{
int i, sign = 1, flag = 0, output;
unsigned int r = 0;

for (i = 0; p[i] != '\0' && flag != 2; i++)
{
if (p[i] == '-')
sign *= -1;

if (p[i] >= '0' && p[i] <= '9')
{
flag = 1;
r *= 10;
r += (p[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -r;
else
output = r;

return (output);
}
