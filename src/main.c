#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void print_prompt1()
{
    fprintf(stderr, "frozesh> ");
}

void print_prompt2(void)
{
    fprintf(stderr, "> ");
} 

/**
 * @brief Read a command of arbitrary length in chunks of 1024 bytes.
*/
char * read_command(void)
{
    char chunk[1024];
    char * command;
    int command_length;

    command = NULL;
    command_length = 0;

    while(fgets(chunk, 1024, stdin))
    {
        int chunk_length;
        
        chunk_length = strlen(chunk);

        if(! command)
        {
            // If command doesn't exist yet, then give memory with malloc
            command = malloc(chunk_length + 1);
        } 
        else 
        {
            // If command exists, then ellongate command with realloc
            char * longer_command;

            longer_command = NULL;
            longer_command = realloc(command, command_length + chunk_length + 1);

            if (longer_command)
            {
                command = longer_command;
            }
            else
            {
                free(command);
                command = NULL;
            }
        }

        if(! command)
        {
            fprintf(stderr, "Error: failed to allocate memory to command: %s\n", strerror(errno));
        }

        strcpy(command + command_length, chunk);

        if(chunk[chunk_length - 1] == '\n')
        {
            if(chunk[chunk_length - 2] != '\\') 
            {
                // If user pressed ENTER and the command 
                // is not multi-line with BACKSLASH
                // then return the command
                return command;
            }
            
            // If the command is multi-line with BACKSLASH
            // then print the second prompt
            print_prompt2();
        }

        command_length += chunk_length;
    }

    return command;
}

char ** tokenizer(char * cmd)
{
    char ** tokens;
    char * token;
    const char * delimiters;
    unsigned int count;

    tokens = malloc(sizeof(cmd));
    delimiters = " \n\\";
    count = 0;

    token = strtok(cmd, delimiters);

    if(token == NULL)
    {
        fprintf(stderr, "Error: failed to tokenize, command is empty %s\n", strerror(errno));
    }

    do
    {
        tokens[count] = token;
        token = strtok(NULL, delimiters);
        count += 1;
    } while (token != NULL);

    return tokens;
}

int main(int argc, char **argv)
{
    char * cmd;

    while(1)
    {
        print_prompt1();
        cmd = read_command();

        // If there is nothing in the command line then exit.
        if (! cmd) 
        {
            exit(EXIT_SUCCESS);
        }

        // If the user just presses enter then continue to the next command.
        if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
        {
            free(cmd);
            continue;
        }

        // If the user enters "exit" then exit
        if (strcmp(cmd, "exit\n") == 0)
        {
            free(cmd);
            break;
        }

        char ** tokens;
        tokens = tokenizer(cmd);

        for (int i = 0; i < 2; i ++)
        {
            char * token = tokens[i];
            printf("%s\n", token);
        }
        
        // Placeholder. Print back the introduced command.
        // printf("%s", cmd);

        free(cmd); // Command was used, hence free
    }

    exit(EXIT_SUCCESS);
}