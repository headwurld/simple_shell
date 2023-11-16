#include "shell.h"

/**
* *_strncpy - Copy a string up to a specified number of characters.
* @des: The destination string to copy to.
* @source: The source string to copy from.
* @name: The maximum number of characters to be copied.
*
* Return: A pointer to the destination string.
*/
char *_strncpy(char *des, char *source, int name)
{
int i;
char *r = des;

i = 0;
while (source[i] != '\0' && i < name - 1)
{
des[i] = source[i];
i++;
}
if (i < name)
{
int k = i;
while (k < name)
{
des[k] = '\0';
k++;
}
}
return (r);
}

/**
* * _strncat - Concatenate two strings with a specified maximum length.
* @s1: The first string.
* @s2: The second string.
* @name: The maximum number of characters to concatenate.
*
* Return: A pointer to the concatenated string.
*/
char *_strncat(char *s1, char *s2, int name)
{
int i, k;
char *r = s1;

i = 0;
k = 0;
while (s1[i] != '\0')
i++;
while (s2[k] != '\0' && k < name)
{
s1[i] = s2[k];
i++;
k++;
}
if (k < name)
s1[i] = '\0';
return (r);
}

/**
* *_strchr - Locate a character in a string.
* @str: The string to be searched.
* @a: The character to look for.
*
* Return: NULL if character is not found.
*/
char *_strchr(char *str, char a)
{
do {
if (*str == a)
return (str);
} while (*str++ != '\0');

return (NULL);
}
