#include "shell.h"

/**
* add_node - Adds a node to the beginning of the list.
* @head: Address of the pointer to the head node.
* @string: String field of the node.
* @num: Node number used in history.
*
* Return: Size of the list.
*/
list_t *add_node(list_t **head, const char *string, int num)
{
list_t *new_head;

if (!head)
return (NULL);

new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);

fill_memory((void *)new_head, 0, sizeof(list_t));
new_head->num = num;

if (string)
{
new_head->string = _strdup(string);

if (!new_head->string)
{
free(new_head);
return (NULL);
}
}

new_head->next = *head;
*head = new_head;

return (new_head);
}

/**
* add_node_end - Adds a node to the end of the list.
* @head: Address of the pointer to the head node.
* @string: String field of the node.
* @num: Node number.
*
* Return: Size of the list.
*/
list_t *add_node_end(list_t **head, const char *string, int num)
{
list_t *new_end, *end;

if (!head)
return (NULL);

end = *head;

new_end = malloc(sizeof(list_t));

if (!new_end)
return (NULL);

fill_memory((void *)new_end, 0, sizeof(list_t));
new_end->num = num;

if (string)
{
new_end->string = _strdup(string);

if (!new_end->string)
{
free(new_end);
return (NULL);
}
}

if (end)
{
while (end->next)
end = end->next;

end->next = new_end;
}
else
*head = new_end;

return (new_end);
}

/**
* print_list_string - Prints only the 'string' element of a list_t linked list.
* @first: Pointer to the first node.
* Return: Size of the list.
*/
size_t print_list_string(const list_t *first)
{
size_t p = 0;

while (first)
{
_puts(first->string ? first->string : "(nil)");
_puts("\n");
first = first->next;
p++;
}

return (p);
}

/**
* delete_node_at_index - Deletes a node at the given index.
* @head: Address of the pointer to the first node.
* @index: Index of the node to delete.
*
* Return: 1 on success, 0 on failure.
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
list_t *node, *old_node;
unsigned int p = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);

return (1);
}

node = *head;

while (node)
{
if (p == index)
{
old_node->next = node->next;
free(node->str);
free(node);

return (1);
}

p++;
old_node = node;
node = node->next;
}
return (0);
}

/**
* _freelist - frees all nodes of on a list
* @h_ptr: Address of pointer to the head node
*
* Return: void
*/
void _freelist(list_t **h_ptr)
{
list_t *node, *next_node, *head;

if (!h_ptr || !*h_ptr)
return;
head = *h_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*h_ptr = NULL;
}
