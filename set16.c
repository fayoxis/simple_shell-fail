#include "shell.h"

/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 * @count: number of pointers to free
 *
 * Return: number of pointers successfully freed.
 */
int bfree(void **ptr)
{
    int freed = 0;

    while (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        freed = 1;
    }

    return freed;
}
/**
 * isExecutableCmd - determines if a file is an executable command
 * @inform: the inform struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutableCmd(inform_t *inform, char *path)
{
    struct stat st;

    (void)inform;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}




/**
 * duplicateChars - duplicates characters
 * @pathstring: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicateChars(const char *pathstring, int start, int stop)
{
    int length = stop - start;
    char *buffer = (char *)malloc((length + 1) * sizeof(char));
  int k = 0;
  int i;

    if (buffer == NULL) {
        return NULL;
    }
  
    for (i = start; i < stop; i++)
    {
        if (pathstring[i] != ':')
        {
            buffer[k] = pathstring[i];
            k++;
        }
    }
    buffer[k] = '\0';
    return buffer;
}
/**
 * findCmdPath - finds this command in the PATH string
 * @inform: the inform struct
 * @pathstring: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
/*char *findCmdPath(inform_t *inform, char *pathstring, char *command)
{
    int current_pos = 0;
    char *path = NULL;
  int i;

    if (!pathstring)
        return NULL;

    if (_strlen(command) > 2 && it_starts_with(command, "./"))
    {
        if (isExecutableCmd(inform, command))
            return command;
    }

    for (i = 0; pathstring[i]; i++)
    {
        int j = i;
        while (pathstring[j] && pathstring[j] != ':')
            j++;

        path = duplicateChars(pathstring, current_pos, j);

        if (!*path)
            _strcat(path, command);
        else
        {
            _strcat(path, "/");
            _strcat(path, command);
        }

        if (isExecutableCmd(inform, path))
            return path;

        if (pathstring[j] == ':')
        {
            i = j + 1;
            current_pos = i;
        }
        else
        {
            break;
        }
    }

    return NULL;
}*/

char *findCmdPath(inform_t *inform, const char *pathstring, const char *command)
{
    const char *delimiter ;
    const char *path;
    const char *end;
    char *fullPath;
    char *lastPath;
    
    if (!pathstring)
        return NULL;

    /* Check if the command is a direct path*/
    if (_strlen(command) > 2 && it_starts_with(command, "./") && isExecutableCmd(inform, command))
        return strdup(command);

    delimiter = ":";
    path = pathstring;

    while ((end = strchr(path, ':')) != NULL)
    {
        fullPath = createFullPath(path, end, command);

        if (fullPath != NULL)
        {
            if (isExecutableCmd(inform, fullPath))
                return fullPath;

            free(fullPath);
        }

        path = end + 1;
    }

    /* Check the last path in the string*/
    lastPath = createFullPath(path, NULL, command);
    if (lastPath != NULL)
    {
        if (isExecutableCmd(inform, lastPath))
            return lastPath;

        free(lastPath);
    }

    return NULL;
}

char *createFullPath(const char *start, const char *end, const char *command)
{
    size_t pathLength = (end != NULL) ? (size_t)(end - start) : strlen(start);
    size_t commandLength = strlen(command);

    char *fullPath = (char *)malloc(pathLength + 1 + commandLength + 1);

    if (fullPath != NULL)
    {
        strncpy(fullPath, start, pathLength);
        fullPath[pathLength] = '\0';

        _strcat(fullPath, "/");
        _strcat(fullPath, command);
    }

    return fullPath;
}

