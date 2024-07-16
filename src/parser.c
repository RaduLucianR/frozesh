#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "parser.h"
#include "tokenizer.h"

struct TreeNode * parser(char ** tokens)
{
    struct TreeNode * ast;
    int token_count;
    int command_count;
    int command_index;
    
    token_count = nrof_tokens(tokens);

    if(token_count < 1)
    {
        fprintf(stderr, "[ERROR] Parser: No tokens to parse!\n");
        exit(1);
    }

    command_index = 0;
    command_count = 1;
    ast = malloc(sizeof(struct TreeNode));
    ast->token = "Command";
    ast->children = NULL;

    // Handle pipes and count commands
    for(int i = 0; i < token_count; i ++)
    {
        if(strcmp(tokens[i], "|") == 0) // if token is pipe
        {  
            if(i == 0)
            {
                fprintf(stderr, "[ERROR] Parser: Pipe operator is not allowed to be a command!\n");
                exit(1);
            }

            if(tokens[i + 1] == NULL)
            {
                fprintf(stderr, "[ERROR] Parser: Right-hand side operand is missing for the pipe operator!\n");
                exit(1);
            }

            if(strcmp(tokens[i + 1], "|") == 0)
            {
                fprintf(stderr, "[ERROR] Parser: Two pipes are not allowed back to back!\n");
                exit(1);
            }
            
            command_count ++;
        }
    }

    ast->children = malloc(sizeof(struct TreeNode) * command_count);

    for(int i = 0; tokens[i] != NULL; i ++)
    {

        if(i == 0 || strcmp(tokens[i - 1], "|") == 0)
        {
            ast->children[command_index] = malloc(sizeof(struct TreeNode));
            ast->children[command_index]->token = tokens[i];
            ast->children[command_index]->children = NULL;
            command_index ++;
            continue;
        }

        if(i > 0 && strcmp(tokens[i], "|") != 0)
        {
            struct TreeNode * cmd;
            int arg_index;

            cmd = malloc(sizeof(struct TreeNode));
            cmd = ast->children[command_index - 1];
            arg_index = 0;

            if(cmd->children != NULL)
            {
                for(arg_index = 0; cmd->children[arg_index] != NULL; arg_index ++) {}

                cmd->children = realloc(cmd->children, sizeof(struct TreeNode) * arg_index); // TODO: implement realloc with in-between value
            } else {
                cmd->children = malloc(sizeof(struct TreeNode));
            }

            cmd->children[arg_index] = malloc(sizeof(struct TreeNode));
            cmd->children[arg_index]->token = tokens[i];
            cmd->children[arg_index]->children = NULL;
            continue;
        }
    }

    return ast;
}

void print_ast(struct TreeNode * node, int level)
{
    if(node != NULL)
    {
        for(int i = 0; i < 4 * level; i ++)
        {
                printf(" ");
        }

        switch (level)
        {
        case 0:
            break;
    
        case 1:
            printf("Cmd: ");
            break;

        case 2:
            printf("Arg: ");
            break;
        }

        printf("%s\n", node->token);
        level += 1;

        if(node->children != NULL)
        {
            for(int i = 0; node->children[i] != NULL; i ++)
            {
                print_ast(node->children[i], level);
            }
        }
    }
}

void free_ast(struct TreeNode * node)
{
    if(node != NULL)
    {
        if(node->children != NULL)
        {
            for(int i = 0; node->children[i] != NULL; i ++)
            {
                free_ast(node->children[i]);
            }
        }

        free(node);
    }
}