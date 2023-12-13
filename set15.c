#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
    char *dest_ptr = dest;
    while ((*dest++ = *src++))
        ;
    return dest_ptr;
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
    size_t length = strlen(str) + 1;
    char *ret = malloc(length);
    if (ret)
        memcpy(ret, str, length);
    return ret;
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
    while (*str)
        _putchar(*str++);
}

/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (ch == BUFFER_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (ch != BUFFER_FLUSH)
        buf[i++] = ch;
    return (1);
}
