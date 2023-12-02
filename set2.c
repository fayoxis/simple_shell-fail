/**
 * setAlias - Sets an alias to a given string.
 * @inform: Pointer to the parameter struct.
 * @str: The string representing the alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int setAlias(inform_t *inform, char *str)
{
    char *equalPos;

    equalPos = _strchr(str, '=');
    if (!equalPos)
        return 1;
    if (!*++equalPos)
        return  remove_alias(inform, str);

     remove_alias(inform, str);
    return addNodeEnd(&(inform->alias), str, 0) == NULL;
}

/**
 * printAlias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int printAlias(list_t *node)
{
    char *equalPos = NULL, *alias = NULL;

    if (node)
    {
        equalPos = _strchr(node->str, '=');
        for (alias = node->str; alias <= equalPos; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(equalPos + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * myAlias - Mimics the alias builtin (man alias).
 * @inform: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0.
 */
int myAlias(inform_t *inform)
{
    int i;
    char *equalPos;
    list_t *node;

    if (inform->argc == 1)
    {
        node = inform->alias;
        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; inform->argv[i]; i++)
    {
        equalPos = _strchr(inform->argv[i], '=');
        if (equalPos)
        {
            setAlias(inform, inform->argv[i]);
        }
    }

    for (i = 1; inform->argv[i]; i++)
    {
        equalPos = _strchr(inform->argv[i], '=');
        if (!equalPos)
        {
            node = findAliasStartsWith(inform->alias, inform->argv[i], '=');
            printAlias(node);
        }
    }

    return 0;
}
