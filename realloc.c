#include "shell.h"

/**
* *fill_memory - fills a memory area with a constant byte
* @dest: the pointer to the memory area
* @byte: the byte to fill the memory with
* @size: the size in bytes to be filled
*
* Return: a pointer to the filled memory area
*/
char *fill_memory(char *dest, char byte, unsigned int size)
{
unsigned int i;

for (i = 0; i < size; i++)
{
dest[i] = byte;
}
return (dest);
}

/**
* free_string_array - frees an array of strings
* @ss: the array of strings to free
*/
void free_string_array(char **ss)
{
char **c = ss;

if (!ss)
return;

while (*ss)
{
free(*ss++);
}
free(c);
}

/**
* _realloc - reallocates a block of memory
* @ptr: the pointer to the previously allocated block
* @p: the size in bytes of the previous block
* @n: the size in bytes of the new block
*
* Return: a pointer to the resized memory block
*/
void *_realloc(void *ptr, unsigned int p, unsigned int n)
{
char *new_ptr;

if (!ptr)
return (malloc(n));

if (!n)
return (free(ptr), NULL);

if (n == p)
return (ptr);

new_ptr = malloc(n);

if (!new_ptr)
return (NULL);

p = p < n ? p : n;

while (p--)
{
new_ptr[p] = ((char *)ptr)[p];
}

free(ptr);

return (new_ptr);
}
