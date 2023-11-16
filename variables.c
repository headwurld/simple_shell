#include "shell.h"

/**
* is_chain - Check if the current character in the buffer is a chain delimiter.
* @info: The parameter structure.
* @buf: The character buffer.
* @p: The address of the current position in buf.
*
* Return: 1 if it's a chain delimiter, 0 otherwise.
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buffer_type = COMMAND_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buffer_type = COMMAND_AND;
}
else if (buf[j] == ';')
{
buf[j] = 0;
info->cmd_buffer_type = COMMAND_CHAIN;
}
else
return (0);
*p = j;
return (1);
}

/**
* check_chain - function to be checked whether chaining on last status.
* @info: The parameter structure.
* @buf: The buffer.
* @p: The address of the current position.
* @i: The starting position in buf.
* @len: The length of buf.
*
* Return: Void.
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (info->cmd_buffer_type == COMMAND_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buffer_type == COMMAND_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}

*p = j;
}

/**
* update_alias - Replace aliases in the tokenized string.
* @info: The parameter structure.
*
* Return: 1 if replaced, 0 otherwise.
*/
int update_alias(info_t *info)
{
int i;
list_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = find_node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}

/**
* varswap - Replace variables in the tokenized string.
* @info: The parameter structure.
*
* Return: 1 if replaced, 0 otherwise.
*/
int varswap(info_t *info)
{
int i = 0;
list_t *node;

for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;

if (!_strcmp(info->argv[i], "$?"))
{
replace_string(&(info->argv[i]),
_strdup(convert_num2base(info->status, 10, 0)));
continue;
}
if (!_strcmp(info->argv[i], "$$"))
{
replace_string(&(info->argv[i]),
_strdup(convert_num2base(getpid(), 10, 0)));
continue;
}
node = find_node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
replace_string(&(info->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&info->argv[i], _strdup(""));
}
return (0);
}

/**
* replace_string - Replace a string.
* @old: The address of the old string.
* @new: The new string.
*
* Return: 1 if replaced, 0 otherwise.
*/
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}

