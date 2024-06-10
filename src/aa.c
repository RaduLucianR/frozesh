#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char buffer[5];
    fgets(buffer, 5, stdin);
    char * a = (char *) malloc(sizeof(5));
    strcpy(a, buffer);
    printf("%s\n", a);
    free(a);
    return 0;
}