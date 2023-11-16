#include "shell.h"

/**
* **strspt - Split a string into individual words
* based on specified delimiters.
* Repeated delimiters are treated as a single delimiter.
* @str: The input string to be divided into words.
* @d: The delimiter string that defines how to split the input.
*
* Return: A pointer to an array of strings containing the words,
* or NULL in case of failure.
*/
char **strspt(char *str, char *d)
{
int a, b, k, m, numwords = 0;
char **r;
if (str == NULL || str[0] == '\0')
return (NULL);
if (!d)
d = " ";
for (a = 0; str[a] != '\0'; a++)
{
if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
numwords++;
}
if (numwords == 0)
return (NULL);
r = malloc((1 + numwords) *sizeof(char *));
if (!r)
return (NULL);
for (a = 0, b = 0; b < numwords; b++)
{
while (is_delim(str[a], d))
a++;
k = 0;
while (!is_delim(str[a + k], d) && str[a + k])
k++;
r[b] = malloc((k + 1) * sizeof(char));
if (!r[b])
{
for (k = 0; k < b; k++)
free(r[k]);
free(r);
return (NULL);
}
for (m = 0; m < k; m++)
r[b][m] = str[a++];
r[b][m] = '\0';
}
r[b] = NULL;
return (r);
}

/**
* **strspt2 - Split a string into individual words
* using a single delimiter character.
* @str: The input string to be divided.
* @d: The delimiter character.
*
* Return: A pointer to an array of strings,
* or NULL on failure.
*/
char **strspt2(char *str, char d)
{
int a, b, k, m, numwords = 0;
char **r;

if (str == NULL || str[0] == '\0')
return (NULL);

for (a = 0; str[a] != '\0'; a++)
{
if ((str[a] != d && str[a + 1] == d) ||
(str[a] != d && !str[a + 1]) || str[a + 1] == d)
numwords++;
}
if (numwords == 0)
return (NULL);
r = malloc((1 + numwords) *sizeof(char *));
if (!r)
return (NULL);
for (a = 0, b = 0; b < numwords; b++)
{
while (str[a] == d && str[a] != d)
a++;
k = 0;
while (str[a + k] != d && str[a + k] && str[a + k] != d)
k++;
r[b] = malloc((k + 1) * sizeof(char));
if (!r[b])
{
for (k = 0; k < b; k++)
free(r[k]);
free(r);
return (NULL);
}
for (m = 0; m < k; m++)
r[b][m] = str[a++];
r[b][m] = '\0';
}
r[b] = NULL;
return (r);
}
