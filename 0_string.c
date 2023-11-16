#include "shell.h"

/**
* _strlen - returns the length of a string
* @str: the string to determine the length of
*
* Return: the length of the string as an integer
*/
int _strlen(char *str)
{
int length = 0;

if (!str)
return (0);

while (*str++)
{
length++;
}

return (length);
}

/**
* _strcmp - performs lexicographic comparison of two strings
* @str1: the first string
* @str2: the second string
*
* Return: a negative value if str1 < str2, a positive
* value if str1 > str2, or zero if str1 == str2
*/
int _strcmp(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);

str1++;
str2++;
}

if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}


/**
 * starts_with_string - checks if one string starts with another
 * @stack: the string to search
 * @pin: the substring to find
 *
 * Return: a pointer to the next character in the original string or NULL
 */
char *starts_with_string(const char *stack, const char *pin)
{
if (!stack || !pin)
return (NULL);
while (*pin && *stack)
{
if (*pin != *stack)
return (NULL);
pin++;
stack++;
}

if (*pin == '\0')
return ((char *)stack);
return (NULL);
}

/**
* _strcat - concatenates two strings
* @destination: the destination buffer
* @src: the source buffer
*
* Return: a pointer to the destination buffer.
*/
char *_strcat(char *destination, char *src)
{
	char *result = destination;

	while (*destination)
	{
		destination++;
	}
	while (*src)
	{
		*destination = *src;
		destination++;
		src++;
	}

	*destination = '\0';
	return (result);
}
