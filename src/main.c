#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void print_prompt1()
{
    fprintf(stderr, "! ");
}

void print_prompt2(void)
{
    fprintf(stderr, "> ");
} 

char * read_command()
{
    char buffer[1024];
    fgets(buffer, 1024, stdin);

    return buffer;
}

int main(int argc, char **argv)
{
    char * cmd;

    do
    {
        print_prompt1();
        cmd = read_command();

        // If there is nothing in the command line then exit.
        if (!cmd) 
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

        printf("%s", cmd); // Place holder. Print back the introduced command.
        free(cmd);
    } while (1);

    exit(EXIT_SUCCESS);
}