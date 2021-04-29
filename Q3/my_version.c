#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main ()
{
    FILE* OS_file;
    char buffer[256];

    OS_file = fopen("/etc/os-release", "r");

    int i = 0;
    printf("OS Information:\n");

    while(!feof(OS_file))
    {
        fscanf(OS_file, "%s", buffer);
        // only display name and version of OS
        if(i < 5)
        {
            printf("%s\n", buffer);

        }
        i++;
    }
    fclose(OS_file);

    FILE* Kernel_file;
    char kernel_buffer[256];

    Kernel_file = fopen("/proc/version", "r");

    int j = 0;
    printf("\n");
    printf("Kernel Information:\n");

    while(!feof(Kernel_file))
    {
        fscanf(Kernel_file, "%s", kernel_buffer);
        // Only display version of kernel
        if(j < 3) {
            printf("%s\n", kernel_buffer);
        }
        j++;
    }
    fclose(Kernel_file);
    return (0);
}