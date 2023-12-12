#include "shell.h"

/**
 * shellLoop - Main shell loop
 * @inform: Pointer to the parameter and return inform struct
 * @args: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shellLoop(inform_t *inform, char **args)
{
    ssize_t inputResult;
    int builtinResult = 0;
    int exitCode = 0;
    int interactiveMode = checkInteractiveMode(inform);

    while (1)
    {
        initialize_shell_inform(inform);

        if (interactiveMode)
            _putchar();

        _puts();
        inputResult = get_input(inform);

        if (inputResult == -1)
        {
            if (interactiveMode)
                printNewLine();
            free_shell_info(inform, 0);
            break;
        }

        set_shell_inform(inform, args);
        builtinResult = findBuiltinCommand(inform);

        if (builtinResult == -1)
            searchAndExecuteCommand(inform);

        free_shell_info(inform, 0);

        if (builtinResult == -2)
        {
            if (inform->errorNumber == -1)
                exitCode = inform->status;
            else
                exitCode = inform->errorNumber;
            break;
        }
    }

    buildHistoryList(inform);
    free_shell_info(inform, 1);

    if (!interactiveMode && inform->status)
        exit_shell(inform->status);

    if (exitCode != 0)
        exit_shell(exitCode);

    return builtinResult;
}

/**
 * findBuiltinCommand - searches for a builtin command in a table.
 * @inform: Pointer to the parameter and return inform struct.
 *
 * Return: -1 if the builtin command is not found,
 *         0 if the builtin command is executed successfully,
 *         1 if the builtin command is found but not successful,
 *         -2 if the builtin command signals an exit().
 */
int findBuiltinCommand(inform_t *inform)
{
    int i = 0, builtinRet = -1;
    builtin_table builtinTable[] = {
        {"exit_shell", exit_shell},
        {"env", printEnvironment},
        {"help", custom_help},
        {"history", display_history},
        {"setenv", _getenv},
        {"unsetenv", setEnvironment},
        {"cd", change_Directory},
        {"alias", setAlias},
        {NULL, NULL}
    };

    while (builtinTable[i].type != NULL)
    {
        if (_strcmp(inform->arguments[0], builtinTable[i].type) == 0)
        {
            inform->line_count++;
            builtinRet = builtinTable[i].func(inform);
            break;
        }
        i++;
    }

    return builtinRet;
}
/**
 * searchAndExecuteCommand - searches for a command in the PATH environment variable
 * @inform: pointer to the parameter and return information structure
 *
 * This function is responsible for finding the specified command in the PATH
 * environment variable and executing it if found. If the command is not found,
 * an error message is printed.
 *
 * Return: void
 */
void searchAndExecuteCommand(inform_t *inform)
{
    char *commandPath = NULL;
    int numArgs = 0;
    int i = 0;

    inform->path = inform->arguments[0];
    if (inform->linecount_flag == 1)
    {
        inform->line_count++;
        inform->linecount_flag = 0;
    }

    /* Count the number of arguments */
    while (inform->argument[i])
    {
        if (!checkDelimiter(inform->argument[i], " \t\n"))
        {
            numArgs++;
        }
        i++;
    }

    if (!numArgs)
    {
        return;
    }

    /* Find the command in the PATH */
    commandPath = findCmdPath(inform, getenv(inform, "PATH="), inform->arguments[0]);
    if (commandPath)
    {
        inform->path = commandPath;
        executeCommand(inform);
    }
    else
    {
        /* Check if the command can be executed directly */
        if ((checkInteractiveMode(inform) || getenv(inform, "PATH=")
        || inform->arguments[0][0] == '/') && is_cmd(inform, inform->arguments[0]))
        {
            executeCommand(inform);
        }
        else if (*(inform->argument) != '\n')
        {
            inform->status = 127;
            print_error_message(inform, "not found\n");
        }
    }
}

/**
 * executeCommand - Forks a child process and executes a command
 * @inform: Pointer to the parameter and return info struct
 *
 * This function forks a child process and uses execve to execute a command specified by the
 * inform struct. It waits for the child process to complete and updates the status accordingly.
 * If there is an error during forking or executing the command, appropriate error messages are displayed.
 *
 * Return: void
 */
void executeCommand(inform_t *inform)
{
    pid_t childPid;
    int status;

    childPid = fork();
    if (childPid == -1)
    {
        perror("Error: Failed to fork");
        return;
    }

    if (childPid == 0)
    {
        if (execve(inform->path, inform->argv, print_error_message(inform)) == -1)
        {
            free_shell_info(inform, 1);
            if (errno == EACCES)
                exit_shell(126);
            exit_shell(1);
        }
        /* Error occurred while executing the command*/
        perror("Error: Failed to execute command");
        exit_shell(1);
    }
    else
    {
        do
        {
            if (waitpid(childPid, &status, 0) == -1)
            {
                perror("Error: Waitpid failed");
                return;
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        if (WIFEXITED(status))
        {
            inform->status = WEXITSTATUS(status);
            if (inform->status == 126)
                print_error_message(inform, "Permission denied\n");
        }
    }
}
