#include "shell.h"

/**
 * _strncpy -its copies a string
 * @str: this is destination string to be copied to
 * @src: this is source string
 * @n: thi is  amount of characters to be copied
 * Return: returns the  concatenated string
 */
char *_strncpy(char *str, const char *src, int n)
{
    int i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        str[i] = src[i];

    for (; i < n; i++)
        str[i] = '\0';

    return str;
}

/**
 * _strncat - it concatenates two strings
 * @str: this is obviously first string
 * @src: this is second string
 * @n: it is amount of bytes to be maximally used
 * Return: returns the concatenated string
 */
char *_strncat(char *str, const char *src, int n)
{
    int str_len = 0;
    int i;
int max_append_len = n;
    int src_len = 0;
    while (str[str_len] != '\0')
        str_len++;

    
    while (src[src_len] != '\0')
        src_len++;
    if (src_len < n)
        max_append_len = src_len;

    for (i = 0; i < max_append_len; i++)
        str[str_len + i] = src[i];

    /* Add the null-terminating character*/
    str[str_len + i] = '\0';

    return str;
}
/**
 * _strchr - it  locates a character in a string
 * @str: this is  string to be parsed
 * @ch: this is character to look for
 * Return: a pointer to the memory area str
 */
char *_strchr(const char *str, char ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
            return (char *)str;

        str++;
    }

    if (ch == '\0')
        return (char *)str;

    return NULL;
}
