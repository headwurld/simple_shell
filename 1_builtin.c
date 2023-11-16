#include "shell.h"

/**
* _myhistory - Displays the command history list, each command
*                   preceded by line numbers starting at 0.
* @info:  Structure with potential arguments.
*
* Return: Always returns 0.
*/
int _myhistory(info_t *info)
{
display_list(info->history);
return (0);
}

/**
* unset_alias - Removes an alias mapping.
* @info: Pointer to a structure containing information about aliases.
* @string: The alias string to be removed.
*
* Return: Returns 0 on success, 1 on error.
*/
int unset_alias(info_t *info, char *string)
{
char *equal_sign, temp;
int ret;

equal_sign = _strchr(string, '=');
if (!equal_sign)
return (1);

temp = *equal_sign;
*equal_sign = '\0';

ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, find_node_starts_with(info->alias, string, -1)));

*equal_sign = temp;
return (ret);
}

/**
* set_alias - Sets an alias mapping to string.
* @info: Pointer to a structure containing information about aliases.
* @string: The alias string to be set.
*
* Return: Returns 0 on success, 1 on error.
*/
int set_alias(info_t *info, char *string)
{
char *p;

p = _strchr(string, '=');
if (!p)
return (1);

if (!*++p)
return (unset_alias(info, string));

unset_alias(info, string);
return (add_node_end(&(info->alias), string, 0) == NULL);
}

/**
* print_alias - Prints an alias mapping.
* @node: The alias node to be printed.
*
* Return: Returns 0 on success, 1 on error.
*/
int print_alias(list_t *node)
{
char *s = NULL, *alias_value = NULL;

if (node)
{
s = _strchr(node->str, '=');
for (alias_value = node->str; alias_value <= s; alias_value++)
_putchar(*alias_value);
_putchar('\'');
_puts(s + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* _myalias - Manages alias mappings.
* @info: Pointer to a structure containing potential arguments.
*
* Return: Returns 0.
*/
int _myalias(info_t *info)
{
int i = 0;
char *equal_sign = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}

for (i = 1; info->argv[i]; i++)
{
equal_sign = _strchr(info->argv[i], '=');
if (equal_sign)
set_alias(info, info->argv[i]);
else
print_alias(find_node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}
