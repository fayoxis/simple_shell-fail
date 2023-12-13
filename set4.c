#include "shell.h"

int printEnvironment(inform_t *inform)
{
    const list_t *node = inform->env;

    while (node != NULL)
    {
        printf("%s\n", node->str);
        node = node->next;
    }

    return 0;
}

char *_getenv(const inform_t *inform, const char *name)
{
    const list_t *node = inform->env;
    char *value = NULL;

    while (node != NULL)
    {
        if (it_starts_with(node->str, name))
        {
            value = strchr(node->str, '=');
            if (value != NULL)
            {
                value++;
                return value;
            }
        }
        node = node->next;
    }

    return NULL;
}

int setEnvironment(inform_t *inform)
{
    if (inform->argumentCount != 3)
    {
        _eputs("Error: Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(inform, inform->arguments[1], inform->arguments[2]))
        return 0;
    return 1;
}

int removeEnvironmentVariable(inform_t *inform)
{
    int i;
    
    if (inform->argumentCount <= 1)
    {
        _eputs("Error: Too few arguments\n");
        return 1;
    }

    for (i = 1; i < inform->argumentCount; i++)
        _unsetenv(inform, inform->arguments[i]);

    return 0;
}

int populateEnvironmentList(inform_t *inform)
{
    list_t *node = NULL;
    size_t i = 0;

    if (environment == NULL)
    {
        _eputs("Error: 'environment' is NULL\n");
        return 1;
    }

    while (environment[i])
    {
        add_newnode(&node, environment[i], 0);
        i++;
    }
    inform->env = node;
    return 0;
}
