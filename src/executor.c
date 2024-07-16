/**
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char * search_path(char * cmd)
{
    char * envvar_path;
    char * new_path;
    char * path;
    int i;
    int idx;
    int count;

    envvar_path = getenv("PATH");
    path = malloc(2); // " " + \0
    new_path = NULL;
    i = 0;
    idx = 0;
    
    /**
     * if(envvar_path[i] == ':')
        {
            printf("%s\n", path);
            path = NULL;
            path = realloc(path, 2);
            idx = 0;
            continue;
        }

        Challenge. This is the output. Why is there "aret_!" on 3rd line??
        Answer: because the string is not null-terminated

        /home/lucian/.local/bin
        /home/lucian/ros2_caret_ws/install/cyclonedds/bin
        /opt/ros/humble/binaret_!
        /home/lucian/.local/bin
        /usr/local/sbin
        /usr/local/bin
        /usr/sbin
        /usr/bin
        /sbin
        /bin
        /usr/games
        /usr/local/games
        /snap/bin
    */
   
    for(i = 0; i < strlen(envvar_path); i ++)
    {
        if(envvar_path[i] == ':')
        {
            path[idx] = '\0';
            printf("%s\n", path);
            path[0] = '\0';
            idx = 0;
            continue;
        }

        path[idx] = envvar_path[i];
        path = realloc(path, idx + 2);
        idx ++;
    }
}