#include "shell.h"

/**
* _clearinfo - Initializes the info_t struct.
* @info: Pointer to the info_t struct.
*/
void _clearinfo(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* _setinfo - Populates the info_t struct.
* @info: Pointer to the info_t struct.
* @av: Argument vector.
*/
void _setinfo(info_t *info, char **av)
{
int p = 0;

info->fname = av[0];
if (info->arg)
{
info->argv = strspt(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
for (p = 0; info->argv && info->argv[p]; p++)
;
info->argc = p;

update_alias(info);
varswap(info);
}
}

/**
* free_info - Frees fields of the info_t struct.
* @info: Pointer to the info_t struct.
* @free_all: Flag indicating whether to free all fields.
*/
void free_info(info_t *info, int free_all)
{
free(info->argv);
info->argv = NULL;
info->path = NULL;
if (free_all)
{
if (!info->cmd_buffer)
free(info->arg);
if (info->env)
_freelist(&(info->env));
if (info->history)
_freelist(&(info->history));
if (info->alias)
_freelist(&(info->alias));
free(info->environ);
info->environ = NULL;
freeAndNull((void **)info->cmd_buffer);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUFFER_FLUSH);
}
}
