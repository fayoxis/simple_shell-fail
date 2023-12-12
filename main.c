#include "shell.h"

int main(void) {
    inform_t inform; /** Initialize the structure with default values */
    ssize_t line_size;
    char *line_buf = NULL;
    size_t line_buf_size = 0;

    initialize_shell_inform(&inform); /** Initialize shell information e.g., populate environment variables */

    while (1) {
        printf("$ "); /** Print the prompt */
        /** Read input from user */
#if USE_GETLINE
        line_size = getline(&line_buf, &line_buf_size, stdin);
#else
        line_size = get_the_Line(&inform, &line_buf, &line_buf_size);
#endif
        if (line_size <= 0) { /** Check for no input or error */
            if (feof(stdin)) { /** Do necessary clean-up if end-of-file is encountered */
                free(line_buf);
                write_the_history(&inform);
                free_shell_info(&inform, 1);
                exit(inform.status);
            }
            continue; /** Continue the loop to prompt for input again in other cases */
        }

        /** Process input */
        inform.argument = line_buf; /** Set the line buffer as the argument to pass around */
        inform.argumentCount = 0; /** Reset argument count since this is a new line */
        if (inform.argument && *inform.argument) { /** If a command is present */
            if (buildHistoryList(&inform, inform.argument, inform.historyCount) != 0) { /** Add command to history */
                /** Handle command execution like tokenizing the input and executing commands */
                /** Handle_execution(&inform); */
            }
        }

        /** Reset line buffer for the next command */
        line_buf = NULL;
        line_buf_size = 0;
    }

    /** Perform clean-up on CTRL+D / exit command */
    if (line_buf) {
        free(line_buf);
    }

    write_the_history(&inform); /** Save history to the file */
    free_shell_info(&inform, 1); /** Free allocated memory */

    return inform.status; /** Return last status */
}
