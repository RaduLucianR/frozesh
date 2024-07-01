#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "reader.h"
#include "tokenizer.h"
#include "parser.h"

int main(int argc, char **argv)
{
    char * cmd;
    cmd = NULL;

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
        struct TreeNode * ast;

        tokens = NULL;
        ast = NULL;
        tokens = tokenizer(cmd);
        ast = parser(tokens);
        print_ast(ast, 0);        

        for(int i = 0; tokens[i] != NULL; i ++)
        {
            free(tokens[i]);
        }

        free(tokens);
        free_ast(ast);
        
        // Placeholder. Print back the introduced command.
        // printf("%s", cmd);

        free(cmd); // Command was used, hence free
    }

    exit(EXIT_SUCCESS);
}