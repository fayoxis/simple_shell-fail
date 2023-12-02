#include "shell.h"

/**
 * exit_shell - Exits the shell
 * @inform: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: Exits the shell with a given exit status.
 *         Returns 0 if inform.argv[0] is not "exit".
 */
int exit_shell(inform_t *inform)
{
    int exit_status;
    int input_valid;

    do
    {
        input_valid = 1;  /* Assume input is valid */

        if (inform->argv[1])  /* If there is an exit argument */
        {
            exit_status = string_to_int(inform->argv[1]);
            if (exit_status == -1)
            {
                inform->status = 2;
                print_error(inform, "Illegal number: ");
                print_string(inform->argv[1]);
                print_character('\n');
                input_valid = 0;  /* Invalid input, repeat the loop */
            }
            else
            {
                inform->err_num = exit_status;
            }
        }
        else
        {
            inform->err_num = -1;
        }
    } while (!input_valid);

    return -2;
}
/**
 * change_Directory - Changes the current directory of the process.
 * @inform: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: Always 0.
 */
int change_Directory(inform_t *inform)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    while (1) {
        s = getcwd(buffer, 1024);
        if (!s)
            _puts("ERROR: Failed to retrieve current working directory\n");

        if (!inform->argv[1]) {
            dir = _getenv(inform, "HOME=");
            if (!dir)
                chdir_ret = chdir((dir = _getenv(inform, "PWD=")) ? dir : "/");
            else
                chdir_ret = chdir(dir);
        }
        else if (_strcmp(inform->argv[1], "-") == 0) {
            if (!_getenv(inform, "OLDPWD=")) {
                _puts(s);
                _putchar('\n');
                break;
            }
            _puts(_getenv(inform, "OLDPWD="));
            _putchar('\n');
            chdir_ret = chdir((dir = _getenv(inform, "OLDPWD=")) ? dir : "/");
        }
        else {
            chdir_ret = chdir(inform->argv[1]);
        }

        if (chdir_ret == -1) {
            print_error(inform, "Failed to change directory to ");
            _eputs(inform->argv[1]);
            _eputchar('\n');
        }
        else {
            _setenv(inform, "OLDPWD", _getenv(inform, "PWD="));
            _setenv(inform, "PWD", getcwd(buffer, 1024));
        }

        break;
    }

    return (0);
}
/**
 * custom_help - changes the current directory of the process
 * @inform: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_help(inform_t *inform)
{
    char **arg = inform->arg;
    int i;

    _puts("The help command is called. This function is not implemented yet.\n");

    for (i = 0; arg[i] != NULL; i++)
    {
        _puts(arg[i]);
    }

    return (0);
}
#include "shell.h"

/**
 * display_history - Displays the history list, one command per line, with line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return 0;
}

/**
 * remove_alias - Removes an alias from the alias list.
 * @info: Parameter struct.
 * @alias: The alias string to be removed.
 *
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *alias)
{
	char *p, c;
	int ret;

	while (1) {
		p = _strchr(alias, '=');
		if (!p)
			return 1;
		c = *p;
		*p = '\0';
		ret = delete_thenotes_AIN(&(info->alias),
		get_thenote_IN(info->alias, node_starts_with(info->alias, alias, -1)));
		*p = c;
		if (ret == 0)
			break;
	}
	
	return ret;
}
