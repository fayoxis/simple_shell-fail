#include "shell.h"

/**
 * strtok - splits a string into words. Repeated delimiters are ignored.
 * @str: the input string
 * @delimiter: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtok(char *str, char *delimiter)
{
    int wordCount = 0;
    char **resultArr;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!delimiter)
        delimiter = " ";

    // Calculate the number of words
    char *temp = str;
    while (*temp)
    {
        if (!checkDelimiter(*temp, delimiter) && (checkDelimiter(*(temp + 1), delimiter) || !*(temp + 1)))
            wordCount++;
        temp++;
    }

    if (wordCount == 0)
        return NULL;

    resultArr = malloc((1 + wordCount) * sizeof(char *));
    if (!resultArr)
        return NULL;

    // Split the string into words
    int i = 0;
    while (*str)
    {
        while (checkDelimiter(*str, delimiter))
            str++;

        int k = 0;
        char *start = str;
        while (!checkDelimiter(*str, delimiter) && *str)
        {
            str++;
            k++;
        }

        resultArr[i] = malloc((k + 1) * sizeof(char));
        if (!resultArr[i])
        {
            for (int j = 0; j < i; j++)
                free(resultArr[j]);
            free(resultArr);
            return NULL;
        }

        strncpy(resultArr[i], start, k);
        resultArr[i][k] = '\0';
        i++;
    }

    resultArr[i] = NULL;
    return resultArr;
}

/**
 * strtok2 - splits a string into words.
 * @str: the input string
 * @delimiter: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtok2(char *str, char delimiter)
{
    int wordCount = 0;
    char **resultArr;

    if (str == NULL || str[0] == '\0')
        return NULL;

    // Calculate the number of words
    char *temp = str;
    while (*temp)
    {
        if ((*temp != delimiter && *(temp + 1) == delimiter) ||
            (*temp != delimiter && !*(temp + 1)) || *(temp + 1) == delimiter)
            wordCount++;
        temp++;
    }

    if (wordCount == 0)
        return NULL;

    resultArr = malloc((1 + wordCount) * sizeof(char *));
    if (!resultArr)
        return NULL;

    // Split the string into words
    int i = 0;
    while (*str)
    {
        while (*str == delimiter && *str)
            str++;

        int k = 0;
        char *start = str;
        while (*str != delimiter && *str)
        {
            str++;
            k++;
        }

        resultArr[i] = malloc((k + 1) * sizeof(char));
        if (!resultArr[i])
        {
            for (int j = 0; j < i; j++)
                free(resultArr[j]);
            free(resultArr);
            return NULL;
        }

        strncpy(resultArr[i], start, k);
        resultArr[i][k] = '\0';
        i++;
    }

    resultArr[i] = NULL;
    return resultArr;
}
