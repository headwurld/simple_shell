#include "shell.h"

/**
* get_environ - Get a copy of the custom environment.
* @info: Pointer to the info structure.
*
* Return: A copy of the custom environment.
*/
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_str_array(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
* _unsetenv - Unset an environment variable.
* @info: Pointer to the info structure.
* @v: The name of the environment variable to unset.
*
* Return: 1 if the variable is successfully unset, 0 otherwise.
*/
int _unsetenv(info_t *info, char *v)
{
list_t *node = info->env;
size_t i = 0;
char *ptr;

if (!node || !v)
return (0);

while (node)
{
ptr = starts_with_string(node->str, v);
if (ptr && *ptr == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
* _setenv - Set or modify an environment variable.
* @info: Pointer to the info structure.
* @v: The name of the environment variable.
* @val: The value to set for the environment variable.
*
* Return: Constant at 0.
*/
int _setenv(info_t *info, char *v, char *val)
{
char *buffer = NULL;
list_t *node;
char *c;

if (!v || !val)
return (0);

buffer = malloc(_strlen(v) + _strlen(val) + 2);
if (!buffer)
return (1);
_strcpy(buffer, v);
_strcat(buffer, "=");
_strcat(buffer, val);
node = info->env;
while (node)
{
c = starts_with_string(node->str, val);
if (c && *c == '=')
{
free(node->str);
node->str = buffer;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buffer, 0);
free(buffer);
info->env_changed = 1;
return (0);
}
