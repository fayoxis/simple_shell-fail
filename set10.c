#include "shell.h"

/**
 * initialize_shell_info - Initializes the info_t struct.
 * @inform: Pointer to the struct.
 */
void initialize_shell_inform(inform_t *inform)
{
    inform->argument = NULL;
    inform->arguments = NULL;
    inform->path = NULL;
    inform->argumentCount = 0;
}

/**
 * set_shell_inform - Initializes the inform_t struct.
 * @inform: Pointer to the struct.
 * @arguments: Argument vector.
 */
void set_shell_inform(inform_t *inform, char **arguments)
{
    int i = 0;

    inform->fname = arguments[0];
    if (inform->arg)
    {
        inform->argv = strttok(inform->arg, " \t");
        if (!inform->argv)
        {
            inform->argv = malloc(sizeof(char *) * 2);
            if (inform->argv)
            {
                inform->argv[0] = _strdup(inform->arg);
                inform->argv[1] = NULL;
            }
        }
        
        i = 0;
        while (inform->argv && inform->argv[i])
        {
            i++;
        }
        inform->argc = i;
        replacealias(inform);
        replacevariables(inform);
    }
}

/**
 * free_shell_info - Frees the fields of the info_t struct.
 * @inform: Pointer to the struct.
 * @freeAll: True if freeing all fields.
 */
void free_shell_info(inform_t *inform, int freeAll)
{
do
{
free_s(inform->arguments);
inform->arguments = NULL;
inform->path = NULL;
if (freeAll)
{
if (!inform->commandBuffer)
free(inform->argument);
if (inform->environment)
freeList((list_t **)&(inform->environment));
if (inform->history)
freeList(&(inform->history));
if (inform->alias)
freeList(&(inform->alias));
free_s(inform->environment);
inform->environment = NULL;
bfree((void **)inform->arguments);
if (inform->readfd > 2)
close(inform->readfd);
_putchar(BUF_FLUSH);
}
} while (0);
}
/**
 * gethistory_file - gets the history file
 * @inform: parameter struct
 *
 * Return: allocated string containing history file
 */
char *gethistory_file(inform_t *inform)
{
    char *buff, *dir;

    dir = _getenv(inform, "HOME=");
    if (!dir)
        return (NULL);
    buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buff)
        return (NULL);
    buff[0] = 0;
    _strcpy(buff, dir);
    _strcat(buff, "/");
    _strcat(buff, HIST_FILE);
    return (buff);
}

/**
 * write_the_history - creates a file, or appends to an existing file
 * @inform: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_the_history(inform_t *inform)
{
    ssize_t fd;
    char *file_name = gethistory_file(inform);
    list_t *node = inform->history;

    if (!file_name)
        return (-1);

    fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_name);
    if (fd == -1)
        return (-1);

    while (node != NULL)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
        node = node->next;
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);
    return (1);
}
