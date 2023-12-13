#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define  HISTORY_MAX	4096

extern char* environment[];
/**
 * struct liststr - this is singly linked list
 * @number: the  number is a field
 * @str: this is a  string
 * @next: this points to the next node
 */
typedef struct liststr
{
	int number;
	char *str;
	struct liststr *next;
} list_t;
/**
 * struct passinginform - Contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct.
 * @argument: A string generated from `getline` containing arguments.
 * @arguments: An array of strings generated from `argument`.
 * @path: A string path for the current command.
 * @argumentCount: The count of arguments.
 * @line_count: The line count.
 * @error_num: The error code for `exit()`.
 * @linecount_flag: If on, count this line of input.
 * @file_name: The program filename.
 * @env: Linked list local copy of `environ`.
 * @history: The history node.
 * @alias: The alias node.
 * @environment: Custom modified copy of `environ` from linked list `env`.
 * @env_changed: On if `environ` was changed.
 * @status: The return status of the last executed command.
 * @commandBuffer: Address of pointer to command buffer, on if chaining.
 * @cmd_buffer_type: Command type (`CMD_type`), `||`, `&&`, or `;`.
 * @readfd: The file descriptor from which to read line input.
 * @historyCount: The history line number count.
 */
typedef struct passinginform
{
    char *argument;
    char **arguments;
    char *path;
    int argumentCount;
    unsigned int line_count;
    int file_des;
    int error_num;
    int linecount_flag;
    char *file_name;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environment;
    int env_changed;
    int status;

    char *commandBuffer; 
    int cmd_buffer_type;
    int readfd;
    int historyCount;
} inform_t;

#define INFO_INIT \
{ \
    NULL,       /* argument */ \
    NULL,       /* arguments */ \
    NULL,       /* path */ \
    0,          /* argumentCount */ \
    0,          /* line_count */ \
    0,          /* file_des */ \
    0,          /* error_num */ \
    0,          /* linecount_flag */\
    NULL,       /* file_name */ \
    NULL,       /* env */ \
    NULL,       /* history */ \
    NULL,       /* alias */ \
    NULL,       /* environment */ \
    0,          /* env_changed */ \
    0,          /* status */ \
    NULL,       /* commandBuffer */ \
    0,          /* cmd_buffer_type */ \
    0,          /* readfd */ \
    0           /* historyCount */ \
}


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inform_t *);
} builtin_table;


int checkInteractiveMode(inform_t *);
int checkDelimiter(char , char *);
int isAlphabetic(int );
int convertStringToInteger(char *);
int exit_shell(inform_t *i);
int change_Directory(inform_t *);
int custom_help(inform_t *);
int display_history(inform_t *);
int remove_alias(inform_t *, char *);
int setAlias(inform_t *, char *);

int printAlias(list_t *);
int myAlias(inform_t *);
int printEnvironment(inform_t *);
char *_getenv(inform_t *, const char *);
int setEnvironment(inform_t *);
int removeEnvironmentVariable(inform_t *);
int populateEnvironmentList(inform_t *);
void _eputs(char *);
int _eputchar(char );
int _putfd(char , int );
int _putsfd(char *, int );
int str_integer(char *);
void print_error_message(inform_t *, char *);
int print_decimal_number(int , int );
char *convert_number_to_string(long int , int , int );
void remove_comments_from_string(char *);
char *_strncpy(char *, const char *, int );
char *_strncat(char *, char *, int );
char *_strchr(const char *, char );
ssize_t buffer_input(inform_t *, char **, size_t *);
ssize_t get_input(inform_t *);
ssize_t read_Buffer(inform_t *, char *, size_t *);

int get_the_Line(inform_t *, char **, size_t *);
char **get_environment(inform_t *);
int _unsetenv(inform_t *, char *);
int _setenv(inform_t *, char *, char *);
void initialize_shell_inform(inform_t *);

void set_shell_inform(inform_t *, char **);
void free_shell_info(inform_t *, int );
char *gethistory_file(inform_t *);
int write_the_history(inform_t *);
int readHistoryFromFile(inform_t *);
int buildHistoryList(inform_t *, char *, int);
int renumberHistory(inform_t *);
void freeList(list_t **);
list_t *add_newnode(list_t **, const char *, int);
list_t *addnode_tothe_end(list_t **, const char *, int num );
size_t print_liststr(const list_t *);
int delete_nodeindex(list_t **, unsigned int );
size_t get_list_length(const list_t *);
char **convert_list_to_strings(list_t *);
size_t print_linked_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char );
ssize_t get_nodeindex(list_t *, list_t *);
int _strlen(char *);
int _strcmp(char *, char *);
char *it_starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char );
int bfree(void **);
int isExecutableCmd(inform_t *, char *);
char *duplicateChars(const char *, int , int );
char *findCmdPath(inform_t *, char *, char *);
char *my_memset(char *, char , unsigned int );
void free_s(char **);
void *my_realloc(void *, unsigned int , unsigned int );
int is_chain_char(inform_t *, char *, size_t *);
void the_check_chain(inform_t *, char *, size_t *, size_t , size_t );
int replacealias(inform_t *);
int replacevariables(inform_t *);
int replace_string(char **, char *);
char **strttok(char *, char *);
char **strttok2(char *, char );
int shellLoop(inform_t *, char **);
int findBuiltinCommand(inform_t *);
void searchAndExecuteCommand(inform_t *);
void executeCommand(inform_t *);
char** initializeEnvironment();


#endif
