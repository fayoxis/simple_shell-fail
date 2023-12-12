#include "shell.h"

int main(void)
{
    inform_t inform = INFO_INIT;
    char *buffer = NULL;
    size_t length = 0;
    ssize_t input_size;

    // Initialize shell environment and read history
    initialize_shell_inform(&inform);
    readHistoryFromFile(&inform);

    // Main shell loop
    while (1)
    {
        // Display prompt and get user input
        _puts("$ ");
        input_size = get_input(&inform);

        if (input_size == -1)
            break; // Exit the shell on EOF

        // Skip empty lines
        if (input_size > 1)
        {
            // Process the command buffer
            remove_comments_from_string(inform.commandBuffer);
            if (replacealias(&inform))
                continue;

            if (replacevariables(&inform))
                continue;

            // Add the command to history
            buildHistoryList(&inform, inform.commandBuffer, inform.line_count);

            // Execute the command (you'll need to implement this)
            // execute_command(&inform);

            // Reset command buffer for the next iteration
            free(inform.commandBuffer);
            inform.commandBuffer = NULL;
        }
    }

    // Write history to file before exiting
    write_the_history(&inform);

    // Free allocated memory
    free_shell_info(&inform, 1);

    return 0;
}
