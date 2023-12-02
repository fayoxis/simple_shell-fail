#include "shell.h"

/**
 * initialize_shell_info - Initializes the info_t struct.
 * @_inform: Pointer to the struct.
 */
void initialize_shell_inform(inform_t *_inform)
{
    _inform->argument = NULL;
    _inform->arguments = NULL;
    _inform->path = NULL;
    _inform->argumentCount = 0;
}

/**
 * set_shell_inform - Initializes the info_t struct.
 * @_inform: Pointer to the struct.
 * @arguments: Argument vector.
 */
void set_shell_inform(inform_t *_inform, char **arguments)
{
    int i = 0;

    _inform->filename = arguments[0];
    if (_inform->argument)
    {
        _inform->arguments = strtow(_inform->argument, " \t");
        if (!_inform->arguments)
        {
            _inform->arguments = malloc(sizeof(char *) * 2);
            if (_inform->arguments)
            {
                _inform->arguments[0] = _strdup(_inform->argument);
                _inform->arguments[1] = NULL;
            }
        }
        for (i = 0; _inform->arguments && _inform->arguments[i]; i++)
            ;
        _inform->argumentCount = i;

        replace_alias(_inform);
        replace_variables(_inform);
    }
}

/**
 * free_shell_info - Frees the fields of the info_t struct.
 * @_inform: Pointer to the struct.
 * @freeAll: True if freeing all fields.
 */
void free_shell_info(inform_t *_inform, int freeAll)
{
    do
    {
        ffree(_inform->arguments);
        _inform->arguments = NULL;
        _inform->path = NULL;
        if (freeAll)
        {
            if (!_inform->commandBuffer)
                free(_inform->argument);
            if (_inform->environment)
                free_list(&(_inform->environment));
            if (_inform->history)
                free_list(&(_inform->history));
            if (_inform->alias)
                free_list(&(_inform->alias));
            ffree(_inform->environ);
            _inform->environ = NULL;
            bfree((void **)_inform->commandBuffer);
            if (_inform->readfd > 2)
                close(_inform->readfd);
            _putchar(BUF_FLUSH);
        }
    } while (0);
}
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
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
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *node = info->history;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
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
