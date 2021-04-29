#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main () 
{
    DIR *proc_dir;
    struct dirent *entry;

    FILE *pid_file;
    char name[128];

    proc_dir = opendir("/proc");
    if(proc_dir == NULL) 
    {
        printf("unable to read directory");
        return (1);
    }


    while((entry = readdir(proc_dir))) 
    {
        char d_name[128];
        strcpy(d_name, entry->d_name);

        if(isdigit(d_name[0]))
        {
            char pathname[128];

            // building string for the pathname containing all process names
            strcpy(pathname, "/proc/");
            strcat(pathname, entry->d_name);
            strcat(pathname, "/cmdline");

            pid_file = fopen(pathname, "r");
            if(pid_file == NULL)
            {
                printf("file could not be read\n");
                return (1);
            }

            fgets(name, 128, pid_file);
            fclose(pid_file);

            // source documentation for strrchr function: https://en.cppreference.com/w/c/string/byte/strrchr
            // acquire a pointer reference to the last slash in the process name
            char * lastSlash = strrchr(name, '/');
            // last slash + 1 will be the name of process without cmdline
            char * name_without_cmdline = lastSlash ? lastSlash + 1 : name;

            printf("name: %s PID: %s\n", name_without_cmdline, entry->d_name);
            strcpy(name_without_cmdline, "");
        }

    }

    closedir(proc_dir);
    return (0);
}

