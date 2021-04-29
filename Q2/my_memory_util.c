#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

float mem_utilisation(float total, float free, float buffers, float cached, float slab);
int isNumber(char *string);

int main ()
{
    FILE *mem_file;
    // temporary buffer for storing memory values
    char buffer[128];
    float mem_vals[1000];

    mem_file = fopen("/proc/meminfo", "r");

    int i = 0;
    float mem_val;
    while(!feof(mem_file))
    {
        fscanf(mem_file, "%s", buffer);
        if(isNumber(buffer))
        {
            // converting each string value to a float
            mem_val = atof(buffer);
            mem_vals[i] = mem_val;
            i++;
        }

    }

    fclose(mem_file);

    // I read the file beforehand to determine the correct indexes 
    float mem_total = mem_vals[0];

    float mem_free = mem_vals[1];

    float mem_buffers = mem_vals[3];

    float mem_cached = mem_vals[4];

    float mem_slab = mem_vals[22];


    float result = mem_utilisation( mem_total,  mem_free,  mem_buffers,  mem_cached,  mem_slab);

    printf("%f\n", result);
    return (0);
}

float mem_utilisation(float total, float free, float buffers, float cached, float slab)
{
    return ((total-free-buffers-cached-slab)/total) * 100;
}

int isNumber(char *string)
{
    // loop through each char in string and verify that it is a digit
    while(*string)
    {
        if(*string < '0' || *string > '9')
        {
            return 0;
        }
        string++;
    }
    return 1;
}