#include "shell.h"

/**
 * is_chain_char - tests if the current character in the buffer is a chain delimiter
 * @inform: the parameter struct
 * @buffer: the character buffer
 * @adr: address of the current position in buffer
 *
 * Return: 1 if it is a chain delimiter, 0 otherwise
 */
int is_chain_char(inform_t *inform, char *buffer, size_t *adr)
{
    size_t i = *adr;

    while (buffer[i] != '\0') {
        if (buffer[i] == '|' && buffer[i + 1] == '|') {
            buffer[i] = 0;
            i++;
            inform->cmd_buf_type = CMD_OR;
            *adr = i;
            return 1;
        } else if (buffer[i] == '&' && buffer[i + 1] == '&') {
            buffer[i] = 0;
            i++;
            inform->cmd_buf_type = CMD_AND;
            *adr = i;
            return 1;
        } else if (buffer[i] == ';') { /* found end of this command */
            buffer[i] = 0; /* replace semicolon with null */
            inform->cmd_buf_type = CMD_CHAIN;
            *adr = i;
            return 1;
        }
        i++;
    }

    *adr = i;
    return 0;
}

/**
 * the_check_chain - checks if we should continue chaining based on the last status
 * @inform: the parameter struct
 * @buffer: the character buffer
 * @adr: address of the current position in buffer
 * @index: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void the_check_chain(inform_t *inform, char *buffer, size_t *adr, size_t index, size_t length)
{
    size_t i = *adr;

    while (buffer[i] != '\0') {
        if (inform->cmd_buf_type == CMD_AND) {
            if (inform->status) {
                buffer[index] = 0;
                i = length;
                *adr = i;
                return;
            }
        }

        if (inform->cmd_buf_type == CMD_OR) {
            if (!inform->status) {
                buffer[index] = 0;
                i = length;
                *adr = i;
                return;
            }
        }

        i++;
    }

    *adr = i;
}
