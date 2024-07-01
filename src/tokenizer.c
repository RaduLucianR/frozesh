#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "tokenizer.h"

int nrof_tokens(char ** tokens)
{
    int counter;

    counter = 0;

    for(int i = 0; tokens[i] != NULL; i ++)
    {
        counter ++;
    }

    return counter;
}

char ** tokenizer(char * cmd)
{
    // Local variable declaration
    char ** tokens;
    char * token;
    const char * delimiters;
    unsigned int count;

    // Local variable initialization
    tokens = malloc(sizeof(char *) * MAX_NROF_TOKENS);
    token = NULL;
    delimiters = " \n\\";
    count = 0;

    for (int i = 0; i < MAX_NROF_TOKENS; i++) {
        tokens[i] = NULL;
    }

    // Logic
    token = strtok(cmd, delimiters);

    if(token == NULL)
    {
        fprintf(stderr, "Error: failed to tokenize, command is empty %s\n", strerror(errno));
    }

    do
    {
        tokens[count] = malloc(strlen(token) + 1);
        //tokens[count] = token; -> this will still point to the location in char * cmd!
        strcpy(tokens[count], token); // while strcpy makes a new memory location
        token = strtok(NULL, delimiters);
        count += 1;
    } while (token != NULL);

    return tokens;
}