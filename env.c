#include "shell.h"


/**
* _myenv - Prints the current environment variables.
* @info: Pointer to a structure containing potential arguments.
* Return: Always 0.
*/
int _myenv(info_t *info)
{
print_list_string(info->env);
return (0);
}

/**
* _getenv - Retrieves the value of an environment variable.
* @info: Pointer to a structure containing potential arguments.
* @var: Name of the environment variable.
* Return: Returns the value of the specified environment variable.
*/
char *_getenv(info_t *info, const char *var)
{
list_t *node = info->env;
char *c;

while (node)
{
c = starts_with_string(node->str, var);
if (c && *c)
return (c);
node = node->next;
}

return (NULL);
}

/**
* _mysetenv - Initializes a new environment variable.
* @info: Pointer to a structure containing potential arguments.
* Return: Always returns 0.
*/
int _mysetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}

if (_setenv(info, info->argv[1], info->argv[2]))
return (0);

return (1);
}

/**
* _myunsetenv - Removes an environment variable.
* @info: Pointer to a structure containing potential arguments.
* Return: Always 0.
*/
int _myunsetenv(info_t *info)
{
int a;

if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}

for (a = 1; a <= info->argc; a++)
_unsetenv(info, info->argv[a]);

return (0);
}

/**
* initialize_enviro_list - Initializes the env linked list.
* @info: Pointer to a structure containing potential arguments.
* Return: Always 0.
*/
int initialize_enviro_list(info_t *info)
{
list_t *node = NULL;
size_t a;

for (a = 0; environ[a]; a++)
add_node_end(&node, environ[a], 0);

info->env = node;
return (0);
}

