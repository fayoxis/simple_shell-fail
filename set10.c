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
 * set_shell_inform - Initializes the info_t struct.
 * @inform: Pointer to the struct.
 * @arguments: Argument vector.
 */
void set_shell_inform(inform_t *inform, char **arguments)
{
    int i = 0;

    inform->file_name = arguments[0];
    if (inform->argument)
    {
        inform->arguments = strtok( inform->argument, " \t");
        if (!inform->arguments)
        {
            inform->arguments = malloc(sizeof(char *) * 2);
            if (inform->arguments)
            {
                inform->arguments[0] = _strdup(inform->argument);
                inform->arguments[1] = NULL;
            }
        }
        for (i = 0; inform->arguments && inform->arguments[i]; i++)
            ;
        inform->argumentCount = i;

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
        free(inform->arguments);
        inform->arguments = NULL;
        inform->path = NULL;
        if (freeAll)
        {
            if (!inform->commandBuffer)
                free(inform->argument);
            if (inform->environment)
                freeList(&(inform->environment));
            if (inform->history)
                freeList(&(inform->history));
            if (inform->alias)
                freeList(&(inform->alias));
            free(inform->environment);
            inform->environment = NULL;
            free((void **)inform->commandBuffer);
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
    char *buf, *dir;

    dir = _getenv(inform, "HOME=");
    if (!dir)
        return (NULL);
    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
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
