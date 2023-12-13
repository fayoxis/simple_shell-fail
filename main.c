
#include "shell.h"
/**
 * main - entry point
 * @arg_c: arg_c count
 * @arg_v: arg_v vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_c, char **arg_v)
{
    inform_t inform[] = {INFO_INIT};
    int fil_d = 2;

    asm ("mov %1, %0\n\t"
		"add $3, %0"
        : "=r"(fil_d)
        : "r"(fil_d));

    if (arg_c == 2)
    {
        fil_d = open(arg_v[1], O_RDONLY);
        if (fil_d == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(arg_v[0]);
                _eputs(": 0: Can't open ");
                _eputs(arg_v[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        inform->readfd = fil_d;
    }

    populateEnvironmentList(inform);
    readHistoryFromFile(inform);
    shellLoop(inform, arg_v);

    return EXIT_SUCCESS;
}
