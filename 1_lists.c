#include "shell.h"

/**
* count_list - Determines the length of a linked list.
* @head: Pointer to the first node.
*
* Return: Size of the list.
*/
size_t count_list(const list_t *head)
{
size_t p = 0;

while (head)
{
head = head->next;
p++;
}
return (p);
}

/**
* list_to_str_array - Converts a list of strings into an array.
* @h: Pointer to the first node.
*
* Return: Array.
*/
char **list_to_str_array(list_t *h)
{
list_t *node = h;
size_t p = count_list(h), j;
char **str_array;
char *str;

if (!h || !p)
return (NULL);
str_array = malloc(sizeof(char *) * (p + 1));
if (!str_array)
return (NULL);
for (p = 0; node; node = node->next, p++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < p; j++)
free(str_array[j]);
free(str_array);
return (NULL);
}

str = _strcpy(str, node->str);
str_array[p] = str;
}
str_array[p] = NULL;
return (str_array);
}

/**
* display_list - Prints all elements of a list_t linked list.
* @head: The first node.
*
* Return: Size of the list.
*/
size_t display_list(const list_t *head)
{
size_t i = 0;

while (head)
{
_puts(convert_num2base(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
i++;
}
return (i);
}

/**
* find_node_starts_with - Returns a node whose string starts with a prefix.
* @node: Ptr to the list head.
* @pref: Str to match.
* @ctr: The next character after the prefix to match.
*
* Return: Matching node or NULL.
*/
list_t *find_node_starts_with(list_t *node, char *pref, char ctr)
{
char *p = NULL;

while (node)
{
p = starts_with_string(node->str, pref);
if (p && ((ctr == -1) || (*p == ctr)))
return (node);
node = node->next;
}
return (NULL);
}

/**
* get_node_index - Gets the index of a node in a linked list.
* @h: List head.
* @node: Pointer.
*
* Return: Index  -1 if not found.
*/
ssize_t get_node_index(list_t *h, list_t *node)
{
size_t k = 0;

while (h)
{
if (h == node)
return (k);
h = h->next;
k++;
}
return (-1);
}
