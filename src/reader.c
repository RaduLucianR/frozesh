#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reader.h"

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
    // Local variable declaration
    char chunk[1024];
    char * command;
    int command_length;

    // Local variable initialization
    command = NULL;
    command_length = 0;
    memset(chunk, 0, sizeof(chunk));

    // Logic
    while(fgets(chunk, 1024, stdin))
    {
        int chunk_length = 0;
        
        chunk_length = strlen(chunk);

        if(! command)
        {
            // If command doesn't exist yet, then give memory with malloc
            command = malloc(chunk_length + 1);

            if (!command) {
                fprintf(stderr, "Error: malloc failed %s\n", strerror(errno));
                return NULL;
            }
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
                return NULL;
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